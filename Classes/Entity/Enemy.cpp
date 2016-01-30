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

USING_NS_CC;

Enemy::Enemy(){
    
}

Enemy::~Enemy()
{
    
}

Enemy * Enemy::create(std::string fileName, float originVelo, cocos2d::Vec2 originPos, int direction){
    auto ret = new (std::nothrow) Enemy();
    if (ret) {
        ret->init(fileName , originVelo, originPos, direction);
        return ret;
    }
    return nullptr;
}

void Enemy::update(float d){
   
    updateRadius(d);
    BaseCar::update(d);
  
}

void Enemy::enterCircleCallBack()
{
    randChangeTrack();
    if (_bChangeTrack) {
        startChangeTrack();
    }
    BaseCar::enterCircleCallBack();
}

void Enemy::randChangeTrack(){
    
    if (_commander->isRandSwitchOn()) {
        if (getTag() == 0) {
            _bChangeTrack = rand_0_1() < CHANGE_PROB ? true : false;
            return ;
        }
        
        switch (_commander->getCurrentStateName()) {
            case g3:
                _bChangeTrack = getPre()->getisChangeTrack();
                break;
                
            case g12:
                if (getTag() == 1) {
                    _bChangeTrack = rand_0_1() < CHANGE_PROB ? true : false;
                }else{
                    _bChangeTrack = getPre()->getisChangeTrack();
                }
                break;
                
            case g111:
                _bChangeTrack = rand_0_1() < CHANGE_PROB ? true : false;
                break;
                
            default:
                break;
        }

    }
    
}

void Enemy::followHead(){
    if (getTag() == 0) {
        return;
    }
    auto head = _commander->getEnemies()->at(0);
    if (head->getTrackState() == TrackState::Normal) {
        if (_curRadius != head->getCurRadius() && _trackState == TrackState::Normal) {
            _bChangeTrack = !_bChangeTrack;
        }
    }
}

void Enemy::enterLineCallBack(){
    BaseCar::enterLineCallBack();
}

void Enemy::reset(){
    BaseCar::reset();
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
        }
    } else if(_trackState == TrackState::ToOuter){
        _curRadius = _curRadius + d * v;
        if (_curRadius >= R_OUTER) {
            _curRadius = R_OUTER;
            _trackState = TrackState::Normal;
        }
    }
}

void Enemy::startChangeTrack()
{
    if (_curRadius == R_OUTER) {
        _trackState = TrackState::ToInner;
    } else if(_curRadius == R_INNER){
        _trackState = TrackState::ToOuter;
    }
}









