//
//  Car.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Car.hpp"

USING_NS_CC;

Car::Car():
_blastRes(nullptr),
_velo(0),
_curTrack(TrackId::outer),
_direction(-1)
{
    
}

Car::~Car()
{
    
}

bool Car::init(float originVelo, cocos2d::Vec2 originPos , int direction)
{
    if (Sprite::init()) {
        _direction = direction;
        _originVelo = originVelo;
        _originPos = originPos;
        setVelo(originVelo);
        setPosition(originPos);
        return true;
    }
    return false;
}

void Car::start()
{
    scheduleUpdate();
}

void Car::pause()
{
    unscheduleUpdate();
}

void Car::stop()
{
    unscheduleUpdate();
}

void Car::reset()
{
    setVelo(_originVelo);
    setPosition(_originPos);
}

void Car::changeTrack()
{
    if (_curTrack == TrackId::inner) {
        _curTrack = TrackId::outer;
    } else {
        _curTrack = TrackId::inner;
    }
}

void Car::update(float delta)
{
    Sprite::update(delta);
    FSM::update(delta);
}

void Car::blast()
{
    setTexture(_blastRes);
    stop();
}
