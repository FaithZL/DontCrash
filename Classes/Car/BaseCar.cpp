//
//  BaseCar.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "BaseCar.hpp"

USING_NS_CC;

BaseCar::BaseCar():
_blastRes(nullptr),
_velo(0),
_curTrack(TrackId::outer),
_direction(-1)
{
    
}

BaseCar::~BaseCar()
{
    
}

bool BaseCar::init(float originVelo, cocos2d::Vec2 originPos , int direction)
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
