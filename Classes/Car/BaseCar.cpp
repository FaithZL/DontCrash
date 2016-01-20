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
_velo(0),
_curTrack(TrackId::outer),
_direction(-1)
{
    _radius[TrackId::inner] = R_INNER;
    _radius[TrackId::outer] = R_OUTER;
}

BaseCar::~BaseCar()
{
    
}

bool BaseCar::init(std::string fileName , float originVelo, cocos2d::Vec2 originPos , int direction)
{
    this->initWithFile(fileName);
    initFSM();
    _direction = direction;
    _originVelo = originVelo;
    _originPos = originPos;
    setVelo(originVelo);
    setPosition(originPos);
    return true;
}

void BaseCar::initFSM()
{
    FSMState state;
    state.setName(CarState::Line);
    state.enterCallback = CC_CALLBACK_0(BaseCar::enterLineCallBack, this);
    state.updateCallback = CC_CALLBACK_1(BaseCar::lineUpdate, this);
    addState(state);
    
    state.setName(CarState::Circle);
    state.enterCallback = CC_CALLBACK_0(BaseCar::enterCircleCallBack, this);
    state.updateCallback = CC_CALLBACK_1(BaseCar::circleUpdate, this);
    addState(state);
    
    setNextState(CarState::Line);
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
            setPositionY(POS_L.y + _radius[_curTrack]);
            setRotation3D(Vec3(0 , 0 , 0));
        }else{
            angle = PI * 3 / 2 - angle;
            setPositionY(POS_L.y - _radius[_curTrack]);
            setRotation3D(Vec3(0 , 0 , - 180));
        }
        deltaX = _radius[_curTrack] * angle;
        setPositionX(POS_R.x - deltaX);
    }else{
        angle = getAngle(POS_L , pos);
        if (pos.y > centerY) {
            angle = PI / 2 - angle;
            setPositionY(POS_L.y + _radius[_curTrack]);
            setRotation3D(Vec3(0 , 0 , 0));
        } else {
            angle = angle - PI * 3 / 2;
            setPositionY(POS_L.y - _radius[_curTrack]);
            setRotation3D(Vec3(0 , 0 , - 180));
        }
        deltaX = _radius[_curTrack] * angle;
        setPositionX(POS_L.x + deltaX);
    }
    
}

void BaseCar::enterCircleCallBack()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto pos = getPosition();
    auto centerX = winSize.width / 2;
    auto centerY = winSize.height / 2;
    auto radius = _radius[_curTrack];
    
    double deltaX;
    
    double angle;
    
    if (pos.x > centerX) {
        deltaX = pos.x - POS_R.x;
        angle = deltaX / radius;
        if (pos.y > centerY) {
            angle = PI / 2 - angle;
        } else {
            angle = PI * 3 / 2 + angle;
        }
        setPositionX(POS_R.x + cos(angle) * radius);
        setPositionY(POS_R.y + sin(angle) * radius);
        setRotation3D(Vec3(0 , 0 , - convertTo180(angle - PI / 2)));
    }else{
        deltaX = POS_L.x - pos.x;
        angle = deltaX / radius;
        if (pos.y > centerY) {
            angle = PI / 2 + angle;
        } else {
            angle = PI * 3 / 2 - angle;
        }
        setPositionX(POS_L.x + cos(angle) * radius);
        setPositionY(POS_L.y + sin(angle) * radius);
        setRotation3D(Vec3(0 , 0 , - convertTo180(angle - PI / 2)));
    }
}

void BaseCar::lineUpdate(float d)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto centerY = winSize.height / 2;
    auto posY = getPositionY();
    
    auto posX = getPositionX();
    
    if (posX < POS_L.x || posX > POS_R.x) {
        _delayedStateName = CarState::Circle;
        return;
    }
    
    if ((_direction == Direction::CCW && posY > centerY) || (_direction == Direction::CW && posY < centerY)) {
        auto newX = posX - d * _velo;
        setPositionX(newX);
    }
    else
    {
        auto newX = posX + d * _velo;
        setPositionX(newX);
    }
    
}

void BaseCar::circleUpdate(float d)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto centerX = winSize.width / 2;
    auto posX = getPositionX();
    
    if (posX > POS_L.x && posX < POS_R.x) {
        _delayedStateName = CarState::Line;
        return;
    }
    
    auto radius = _radius[_curTrack];
    //base of PI
    auto angleVelo = _velo / radius;
    //base of 180°
    auto rotateZ = getRotation3D().z;

    auto curAngle = convertToPI(- rotateZ) + PI / 2;
    
    double newAngle;
    
    switch (_direction) {
        case Direction::CCW:
            newAngle = curAngle + angleVelo * d;
            if (posX < centerX){
                setPositionX(POS_L.x + cos(newAngle) * radius);
                setPositionY(POS_L.y + sin(newAngle) * radius);
            }
            else{
                setPositionX(POS_R.x + cos(newAngle) * radius);
                setPositionY(POS_R.y + sin(newAngle) * radius);
            }
            break;
            
        case Direction::CW:
            newAngle = curAngle - angleVelo * d;
            if (posX < centerX) {
                setPositionX(POS_L.x + cos(newAngle) * radius);
                setPositionY(POS_L.y + sin(newAngle) * radius);
            }
            else{
                setPositionX(POS_R.x + cos(newAngle) * radius);
                setPositionY(POS_R.y + sin(newAngle) * radius);
            }
            break;
            
        default:
            break;
    }
    setRotation3D(Vec3(0 , 0 , - convertTo180(newAngle - PI / 2)));
}

void BaseCar::start()
{
    scheduleUpdate();
}

void BaseCar::pause()
{
    unscheduleUpdate();
}


void BaseCar::reset()
{
    setVelo(_originVelo);
    setPosition(_originPos);
}

void BaseCar::changeTrack()
{
    if (_curTrack == TrackId::inner) {
        _curTrack = TrackId::outer;
    } else {
        _curTrack = TrackId::inner;
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
