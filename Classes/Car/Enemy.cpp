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
_trackState(TrackState::Disabled),
_bAttempToChange(false)
{
    
}

Enemy::~Enemy()
{
    
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
    if (_bAttempToChange) {
        changeTrack();
        _bAttempToChange = false;
    }
}

void Enemy::updateRadius(float d)
{
    auto v = _curVelo / 7;
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

void Enemy::changeTrack()
{
    if (_curRadius == R_OUTER) {
        _trackState = TrackState::ToInner;
    } else {
        _trackState = TrackState::ToOuter;
    }
}









