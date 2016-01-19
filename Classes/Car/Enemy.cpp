//
//  Enemy.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Enemy.hpp"


Enemy::Enemy()
{
    
}

Enemy::~Enemy()
{
    
}

void Enemy::update(float d)
{
    BaseCar::update(d);
}

Enemy * Enemy::create(std::string fileName, float originVelo, cocos2d::Vec2 originPos, int direction)
{
    auto ret = new (std::nothrow) Enemy();
    if (ret) {
        ret->init(fileName , originVelo, originPos, direction);
        return ret;
    }
    return nullptr;
}

void Enemy::changeTrack()
{
    BaseCar::changeTrack();
}