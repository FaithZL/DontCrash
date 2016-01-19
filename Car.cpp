//
//  Car.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Car.hpp"

Car::Car()
{
    
}

Car::~Car()
{
    
}

Car * Car::create(std::string fileName, float originVelo, cocos2d::Vec2 originPos, int direction)
{
    auto ret = new (std::nothrow) Car();
    if (ret && ret->init(fileName,originPos, originPos, direction)) {
        return ret;
    }
    return nullptr;
}

void Car::update(float d)
{
    BaseCar::update(d);
}

void Car::changeTrack()
{
    BaseCar::changeTrack();
}