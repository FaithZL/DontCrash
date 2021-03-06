//
//  Car.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Car.hpp"
#include "../constant.h"
USING_NS_CC;

Car::Car()
{
    for (int i = 0 ; i < 3 ; i ++) {
        _extraScore[i] = 0;
        _preDis[i] = 0;
        _bFarthestFlag[i] = false;
    }
}

Car::~Car()
{
    
}

Car * Car::create(std::string fileName, float originVelo, cocos2d::Vec2 originPos, int direction)
{
    auto ret = new (std::nothrow) Car();
    if (ret) {
        ret->init(fileName, originVelo, originPos, direction);
        return ret;
    }
    return nullptr;
}

void Car::update(float d)
{
    updateRadius(d);
    BaseCar::update(d);
    for (int i = 0 ; i < 3 ; i ++) {
        _extraScore[i] = _extraScore[i] - d * 60;
        if (_extraScore[i] <= 0) {
            _extraScore[i] = 0;
        }
    }
}

void Car::updateRadius(float d){
    
    auto v = _curVelo * CAR_R_CHANGE_FACTOR;
    if (_trackState == TrackState::ToInner) {
        _curRadius = _curRadius - d * v;
        if (_curRadius <= R_INNER) {
            _curRadius = R_INNER;
            _trackState = TrackState::Normal;
        }
    } else if(_trackState == TrackState::ToOuter){
        _curRadius = _curRadius + d * v;
        if (_curRadius >= R_OUTER) {
            _curRadius = R_OUTER;
            _trackState = TrackState::Normal;
        }
    }
    
}

void Car::reset(){
    BaseCar::reset();
    
    for (int i = 0 ; i < 3 ; i ++) {
        _extraScore[i] = 0;
        _preDis[i] = 0;
        _bFarthestFlag[i] = false;
    }
}

void Car::changeTrack()
{
    if (_curRadius == R_OUTER) {
        _trackState = TrackState::ToInner;
    } else if(_curRadius == R_INNER){
        _trackState = TrackState::ToOuter;
    }
}





