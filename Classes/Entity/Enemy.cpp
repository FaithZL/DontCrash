//
//  Enemy.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Enemy.hpp"
#include "../constant.h"
#include "../Logic/Commander.hpp"


Enemy::Enemy():
_attempToChange(AttempToChange::CanSet)
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

//void Enemy::circleUpdate(float d)
//{
//    updateRadius(d);
//    BaseCar::circleUpdate(d);
//}

void Enemy::update(float d){
   
    updateRadius(d);
    BaseCar::update(d);
  
}

void Enemy::enterCircleCallBack()
{
    BaseCar::enterCircleCallBack();
    
    if (_attempToChange == AttempToChange::True) {
        changeTrack();
        setAttempToChange(CanSet);
    }else if (_attempToChange == AttempToChange::False){
        setAttempToChange(CanSet);
    }
}

void Enemy::randChangeTrack(){
    switch (_commander->getCurrentStateName()) {
        case g3:
            
            break;
        
        case g12:
            
            break;
            
        case g111:
            
            break;
            
        default:
            break;
    }
}

void Enemy::enterLineCallBack(){
    BaseCar::enterLineCallBack();
//    _attempToChange = AttempToChange::CanSet;
}

void Enemy::reset(){
    BaseCar::reset();
    _attempToChange = AttempToChange::CanSet;
    _trackState = TrackState::Normal;
}

Enemy * Enemy::getPre(){
    if (getTag() > 0) {
        return _commander->getEnemies()->at(getTag() - 1);
    }
    return nullptr;
}

Enemy * Enemy::getNext(){
    if (getTag() < _commander->getEnemies()->size() - 1) {
        return _commander->getEnemies()->at(getTag() + 1);
    }
    return  nullptr;
}

void Enemy::updateRadius(float d)
{
    auto v = _curVelo * ENEMY_R_CHANGE_FACTOR;
    if (_trackState == TrackState::ToInner) {
        _curRadius = _curRadius - d * v;
        if (_curRadius <= R_INNER) {
            _curRadius = R_INNER;
            _trackState = TrackState::Normal;
//            _attempToChange = AttempToChange::CanSet;
        }
    } else if(_trackState == TrackState::ToOuter){
        _curRadius = _curRadius + d * v;
        if (_curRadius >= R_OUTER) {
            _curRadius = R_OUTER;
            _trackState = TrackState::Normal;
//             _attempToChange = AttempToChange::CanSet;
        }
    }
}

void Enemy::changeTrack()
{
    if (_curRadius == R_OUTER) {
        _trackState = TrackState::ToInner;
    } else if(_curRadius == R_INNER){
        _trackState = TrackState::ToOuter;
    }
}









