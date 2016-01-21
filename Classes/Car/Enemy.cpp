//
//  Enemy.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Enemy.hpp"
#include "constant.h"

Enemy::Enemy():
_changeState(ChangeState::Disabled)
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

void Enemy::circleUpdate(float d)
{
    updateRadius(d);
    BaseCar::circleUpdate(d);
}

void Enemy::enterCircleCallBack()
{
    BaseCar::enterCircleCallBack();
    if (rand() % 100 < 30 && _changeState == ChangeState::Normal) {
        changeTrack();
    }
}

void Enemy::updateRadius(float d)
{
    auto v = 100;
    if (_changeState == ChangeState::ToInner) {
        _curRadius = _curRadius - d * v;
        if (_curRadius <= R_INNER) {
            _curRadius = R_INNER;
            _changeState = ChangeState::Normal;
        }
    } else if(_changeState == ChangeState::ToOuter){
        _curRadius = _curRadius + d * v;
        if (_curRadius >= R_OUTER) {
            _curRadius = R_OUTER;
            _changeState = ChangeState::Normal;
        }
    }
}

void Enemy::changeTrack()
{
    if (_curRadius == R_OUTER) {
        _changeState = ChangeState::ToInner;
    } else {
        _changeState = ChangeState::ToOuter;
    }
}









