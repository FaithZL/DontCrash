//
//  BaseCar.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "BaseCar.hpp"
#include "FSMState.h"
#include "Z_Math.h"

USING_NS_CC;

BaseCar::BaseCar():
_curVelo(0),
_direction(-1),
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
    _curVelo = originVelo;
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
        deltaX = _curRadius * angle;
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
        deltaX = _curRadius * angle;
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
        angle = deltaX / _curRadius;
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
        angle = deltaX / _curRadius;
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
    auto posX = getPositionX();
    
    if (UDLR == right || UDLR == left) {
        _delayedStateName = CarState::Circle;
        return;
    }
    
    if ((_direction == Direction::CCW && UDLR == up) || (_direction == Direction::CW && UDLR == down)) {
        auto newX = posX - d * _curVelo;
        setPositionX(newX);
    }
    else
    {
        auto newX = posX + d * _curVelo;
        setPositionX(newX);
    }
    
}

void BaseCar::circleUpdate(float d)
{
    auto UDLR = getUDLR();
    
    if (UDLR == up || UDLR == down) {
        _delayedStateName = CarState::Line;
        return;
    }
    
    //base of PI
    auto angleVelo = _curVelo / _curRadius;
    //base of 180°
    auto rotateZ = getRotation3D().z;

    auto curAngle = convertToPI(- rotateZ) + PI / 2;
    
    double newAngle;
    
    switch (_direction) {
        case Direction::CCW:
            newAngle = curAngle + angleVelo * d;
            if (UDLR == left){
                setPositionX(POS_L.x + cos(newAngle) * _curRadius);
                setPositionY(POS_L.y + sin(newAngle) * _curRadius);
            }
            else{
                setPositionX(POS_R.x + cos(newAngle) * _curRadius);
                setPositionY(POS_R.y + sin(newAngle) * _curRadius);
            }
            break;
            
        case Direction::CW:
            newAngle = curAngle - angleVelo * d;
            if (UDLR == left) {
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

void BaseCar::reset()
{
    setVelo(_originVelo , true);
    setPosition(_originPos);
    setTexture(_normalRes);
    _curRadius = R_OUTER;
    setRotation3D(Vec3(0 , 0 , _originAngle));
}

void BaseCar::changeTrack()
{
    if (_curRadius == R_OUTER) {
        _curRadius = R_INNER;
    } else {
        _curRadius = R_OUTER;
    }
}

void BaseCar::update(float delta)
{
    Sprite::update(delta);
    FSM::update(delta);
}

void BaseCar::blast()
{
    setTexture(_blastRes);
}
