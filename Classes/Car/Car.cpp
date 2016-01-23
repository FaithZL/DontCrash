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
    BaseCar::update(d);
    for (int i = 0 ; i < 3 ; i ++) {
        _extraScore[i] = _extraScore[i] - d * 60;
        if (_extraScore[i] <= 0) {
            _extraScore[i] = 0;
        }
    }
}

float Car::getPreDistance(int enemyTag){
    return _preDis[enemyTag];
}

void Car::setFarthestFlagbyTag(int enemyTag , bool flag){
    _bFarthestFlag[enemyTag] = flag;
}

bool Car::getFarthestFlagbyTag(int enemyTag){
    return _bFarthestFlag[enemyTag];
}

void Car::setDistance(int enemyTag, float distance){
    _preDis[enemyTag] = distance;
}

void Car::setExtraScoreByTag(int enemyTag){
    _extraScore[enemyTag] = 30;
}

float Car::getExtraScoreByTag(int enemyTag){
    return _extraScore[enemyTag];
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