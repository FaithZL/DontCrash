//
//  BaseCar.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "BaseCar.hpp"
#include "../utils/FSM/FSMState.h"
#include "../utils/Z_Math.h"
#include "../constant.h"

USING_NS_CC;

BaseCar::BaseCar():
_curVelo(0),
_angVelo(0),
_direction(-1),
_trackState(TrackState::Normal),
_curRadius(R_OUTER)
{
}

BaseCar::~BaseCar()
{
    
}

bool BaseCar::init(std::string fileName , float originVelo, cocos2d::Vec2 originPos , int direction)
{
    this->initWithFile(fileName);
    _normalRes = fileName;
    _originAngle = getRotation3D().z;
    _direction = direction;
    _originVelo = originVelo;
    _originPos = originPos;
    setVelo(originVelo , true);
    setPosition(originPos);
    initFSM();
    return true;
}

void BaseCar::initFSM()
{
    FSMState line;
    line.setName(CarState::Line);
    line.enterCallback = CC_CALLBACK_0(BaseCar::enterLineCallBack, this);
    line.updateCallback = CC_CALLBACK_1(BaseCar::lineUpdate, this);
    addState(line);
    
    FSMState circle;
    circle.setName(CarState::Circle);
    circle.enterCallback = CC_CALLBACK_0(BaseCar::enterCircleCallBack, this);
    circle.updateCallback = CC_CALLBACK_1(BaseCar::circleUpdate, this);
    addState(circle);
    
    setNextState(CarState::Line);
}

int BaseCar::getUDLR(){
    auto pos = getPosition();
    if (pos.x >=  POS_L.x && pos.x <= POS_R.x) {
        if (pos.y > POS_L.y) {
            return up;
        }else{
            return down;
        }
    }else{
        if (pos.x > POS_L.x) {
            return right;
        } else {
            return left;
        }
    }
}

void BaseCar::enterLineCallBack()
{
    if (getPreviousStateName() == -1) {
        return;
    }
    auto winSize = Director::getInstance()->getWinSize();
    auto pos = getPosition();
    auto centerX = winSize.width / 2;
    auto centerY = winSize.height / 2;
    
    double angle;
    
    double deltaX;
    
    if (pos.x > centerX) {
        angle = getAngle(POS_R , pos);
        if (pos.y > centerY) {
            angle = angle - PI / 2;
            setPositionY(POS_L.y + _curRadius);
            setRotation3D(Vec3(0 , 0 , 0));
        }else{
            angle = PI * 3 / 2 - angle;
            setPositionY(POS_L.y - _curRadius);
            setRotation3D(Vec3(0 , 0 , - 180));
        }
        deltaX = R_OUTER * angle;
        setPositionX(POS_R.x - deltaX);
    }else{
        angle = getAngle(POS_L , pos);
        if (pos.y > centerY) {
            angle = PI / 2 - angle;
            setPositionY(POS_L.y + _curRadius);
            setRotation3D(Vec3(0 , 0 , 0));
        } else {
            angle = angle - PI * 3 / 2;
            setPositionY(POS_L.y - _curRadius);
            setRotation3D(Vec3(0 , 0 , - 180));
        }
        deltaX = R_OUTER * angle;
        setPositionX(POS_L.x + deltaX);
    }
}

void BaseCar::enterCircleCallBack()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto pos = getPosition();
    auto centerX = winSize.width / 2;
    auto centerY = winSize.height / 2;
    
    double deltaX;
    
    double angle;
    
    if (pos.x > centerX) {
        deltaX = pos.x - POS_R.x;
        angle = deltaX / R_OUTER;
        if (pos.y > centerY) {
            angle = PI / 2 - angle;
        } else {
            angle = PI * 3 / 2 + angle;
        }
        setPositionX(POS_R.x + cos(angle) * _curRadius);
        setPositionY(POS_R.y + sin(angle) * _curRadius);
        setRotation3D(Vec3(0 , 0 , - convertTo180(angle - PI / 2)));
    }else{
        deltaX = POS_L.x - pos.x;
        angle = deltaX / R_OUTER;
        if (pos.y > centerY) {
            angle = PI / 2 + angle;
        } else {
            angle = PI * 3 / 2 - angle;
        }
        setPositionX(POS_L.x + cos(angle) * _curRadius);
        setPositionY(POS_L.y + sin(angle) * _curRadius);
        setRotation3D(Vec3(0 , 0 , - convertTo180(angle - PI / 2)));
    }
    
}

void BaseCar::lineUpdate(float d)
{
    auto UDLR = getUDLR();
    
    if (UDLR == right || UDLR == left) {
        _delayedStateName = CarState::Circle;
    }
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    auto pos = getPosition();

    if ((_direction == Direction::CCW && pos.y > centerPos.y) || (_direction == Direction::CW && pos.y < centerPos.y)) {
        auto newX = pos.x - d * _curVelo;
        setPositionX(newX);
        if (pos.y > centerPos.y) {
            setPositionY(POS_L.y + _curRadius);
        }else{
            setPositionY(POS_L.y - _curRadius);
        }
    }
    else
    {
        auto newX = pos.x + d * _curVelo;
        setPositionX(newX);
        if (pos.y > centerPos.y) {
            setPositionY(POS_L.y + _curRadius);
        }else{
            setPositionY(POS_L.y - _curRadius);
        }
    }
}

void BaseCar::circleUpdate(float d)
{
    auto UDLR = getUDLR();
    
    if (UDLR == up || UDLR == down) {
        _delayedStateName = CarState::Line;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    auto pos = getPosition();
    
    //base of 180°
    auto rotateZ = getRotation3D().z;

    auto curAngle = convertToPI(- rotateZ) + PI / 2;
    
    double newAngle;
    
    switch (_direction) {
        case Direction::CCW:
            newAngle = curAngle + _angVelo * d;
            if (pos.x < centerPos.x){
                setPositionX(POS_L.x + cos(newAngle) * _curRadius);
                setPositionY(POS_L.y + sin(newAngle) * _curRadius);
            }
            else{
                setPositionX(POS_R.x + cos(newAngle) * _curRadius);
                setPositionY(POS_R.y + sin(newAngle) * _curRadius);
            }
            break;
            
        case Direction::CW:
            newAngle = curAngle - _angVelo * d;
            if (pos.x < centerPos.x) {
                setPositionX(POS_L.x + cos(newAngle) * _curRadius);
                setPositionY(POS_L.y + sin(newAngle) * _curRadius);
            }
            else{
                setPositionX(POS_R.x + cos(newAngle) * _curRadius);
                setPositionY(POS_R.y + sin(newAngle) * _curRadius);
            }
            break;
            
        default:
            break;
    }
    setRotation3D(Vec3(0 , 0 , - convertTo180(newAngle - PI / 2)));
}

bool BaseCar::isPassX(float x){
    if (_prePos.x < x && getPositionX() >= x) {
        return true;
    }else if (_prePos.x > x && getPositionX() <= x) {
        return true;
    }else{
        return false;
    }
}

bool BaseCar::isPassY(float y){
    if (_prePos.y < y && getPositionY() >= y) {
        return true;
    }else if (_prePos.y > y && getPositionY() <= y){
        return true;
    }else{
        return false;
    }
}

void BaseCar::relieve(){
    _curVelo = _normalVelo * 0.9;
    _angVelo = _curVelo / R_OUTER;
}

void BaseCar::difficultyUp(){
    setVelo(_normalVelo + 20 , true);
}

void BaseCar::reset()
{
    setVelo(_originVelo , true);
    resetFSM();
    setPosition(_originPos);
    setTexture(_normalRes);
    _curRadius = R_OUTER;
    _trackState = TrackState::Normal;
    setRotation3D(Vec3(0 , 0 , _originAngle));
}

void BaseCar::update(float delta)
{
    _prePos = getPosition();
    Sprite::update(delta);
    FSM::update(delta);
}

void BaseCar::blast()
{
    setTexture(_blastRes);
}
