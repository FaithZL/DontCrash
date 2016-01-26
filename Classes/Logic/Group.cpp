//
//  Group.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/25.
//
//

#include "Group.hpp"
#include "Scorer.hpp"
#include "Enemy.hpp"
#include "FSMState.h"
#include "Z_Math.h"

USING_NS_CC;

Group::Group():
_bCanSwitch(false),
_scorer(nullptr){
    
}

Group::~Group(){
    
}

bool Group::init(){
    initFSM();
    return true;
}

void Group::initFSM(){
    FSMState g3;
    g3.setName(EnemyState::g3);
    g3.enterCallback = CC_CALLBACK_0(Group::g3enter, this);
    g3.updateCallback = CC_CALLBACK_1(Group::g3update, this);
    
    FSMState g12;
    g12.setName(EnemyState::g12);
    g12.enterCallback = CC_CALLBACK_0(Group::g12enter, this);
    g12.updateCallback = CC_CALLBACK_1(Group::g12update, this);
    
    FSMState g111;
    g111.setName(EnemyState::g111);
    g111.enterCallback = CC_CALLBACK_0(Group::g111enter, this);
    g111.updateCallback = CC_CALLBACK_1(Group::g111update, this);
    
    addState(g3);
    addState(g12);
    addState(g111);
    
    setNextState(EnemyState::g3);
    
}

float Group::distanceInTrack(Enemy * front , Enemy * back){
    auto fPos = front->getPosition();
    auto bPos = back->getPosition();
    auto radius = front->getCurRadius();
    
    if (front->getUDLR() == left) {
        
        auto fAngle = getAngle(fPos , POS_L);
        auto fArc = radius * (fAngle - PI / 2);
        
        if (back->getUDLR() == up) {
            
            return fArc + (bPos.x - POS_L.x);
            
        }else if (back->getUDLR() == left){
            
            return (fAngle - getAngle(POS_L, bPos)) * radius;
        
        }else if (back->getUDLR() == down){
        
            return (fArc + (POS_R.x - POS_L.x) + PI * radius + (POS_R.x - bPos.x));
            
        }else if (back->getUDLR() == right){
            
            auto bAngle = getAngle(POS_R, bPos);
            
            bAngle = 2.5 * PI - bAngle;
            
            auto bArc = bAngle * radius;
            
            return fArc + bArc + (POS_R.x - POS_L.x);
            
        }
    }else if (front->getUDLR() == right){
        auto fAngle = getAngle(fPos , POS_R);
        fAngle = 2.5 * PI - fAngle;
        
        if (back->getUDLR() == left) {
            
            auto circumference = 2 * (POS_R.x - POS_L.x) + 2 * PI * radius;
            
            return circumference - distanceInTrack(back, front);
        
        }else if (back->getUDLR() == right){
            
            auto bAngle = getAngle(POS_R, bPos);
            
            bAngle = 2.5 * PI - bAngle;
            
            return fabsf(bAngle - fAngle) * radius;
            
        }else if (back->getUDLR() == up){
            
            
            
        }
        
    }
}

void Group::g3enter(){
    
}

void Group::g3update(float d){
    
    
    int i;
    for (i = 0; i < _enemies.size(); i++) {
        if (_enemies.at(i)->getAttempToChange() != AttempTochange::CanSet) {
            break;
        }
    }
    if (i == _enemies.size()) {
        float num = rand_0_1();
        for (i = 0 ; i < _enemies.size(); i++) {
            int var = num < 0.5 ? AttempTochange::True : AttempTochange::False;
            _enemies.at(i)->setAttempToChange(var);
        }
    }
    
    if (_scorer->getCircleCount() >= 1 && _enemies.at(1)->isChangeToCircle()) {
        
        _delayedStateName = EnemyState::g12;
        
    }
}

void Group::g12enter(){
    _enemies.at(1)->speedDown();
    _enemies.at(2)->speedDown();
    
}

void Group::g12update(float d){
    
}

void Group::g111enter(){
    
}

void Group::g111update(float d){
    
}

cocos2d::Vector<Enemy *> * Group::getEnemies(){
    return &_enemies;
}

void Group::update(float d){
    FSM::update(d);
    for (auto iter : _enemies) {
        iter->update(d);
    }
}

void Group::reset(){
    _delayedStateName = EnemyState::g3;
    for(auto iter : _enemies){
        iter->reset();
    }
}

void Group::addEnemy(Enemy *enemy){
    enemy->setGroup(this);
    _enemies.pushBack(enemy);
}



