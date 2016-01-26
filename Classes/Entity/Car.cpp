//
//  Car.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Car.hpp"
#include "constant.h"
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
    _prePos = getPosition();
    BaseCar::update(d);
    for (int i = 0 ; i < 3 ; i ++) {
        _extraScore[i] = _extraScore[i] - d * 60;
        if (_extraScore[i] <= 0) {
            _extraScore[i] = 0;
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
    BaseCar::changeTrack();
    auto pos = getPosition();
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    if (getCurrentStateName() == CarState::Line) {
        if (pos.y > centerPos.y) {
            setPositionY(POS_R.y + _curRadius);
        }
        else{
            setPositionY(POS_R.y - _curRadius);
        }
    }
}