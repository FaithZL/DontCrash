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
//    if (_scorer->getScore() >= 7) {
//        _delayedStateName = EnemyState::g12;
//    }
}

void Group::g12enter(){
    int velo = _enemies.at(1)->getVelo();
    
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
    for(auto iter : _enemies){
        iter->reset();
    }
}

void Group::addEnemy(Enemy *enemy){
    _enemies.pushBack(enemy);
}



