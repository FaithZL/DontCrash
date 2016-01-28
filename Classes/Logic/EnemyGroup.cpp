//
//  Group.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/25.
//
//

#include "EnemyGroup.hpp"
#include "Scorer.hpp"
#include "Enemy.hpp"
#include "FSMState.h"
#include "Z_Math.h"

USING_NS_CC;

EnemyGroup::EnemyGroup():
_timer(0),
_scorer(nullptr),
_randSwitch(RandSwitch::Off){
    
}

EnemyGroup::~EnemyGroup(){
    
}

bool EnemyGroup::init(){
    initFSM();
    return true;
}

void EnemyGroup::initFSM(){
    FSMState g3;
    g3.setName(GroupState::g3);
    g3.enterCallback = CC_CALLBACK_0(EnemyGroup::g3enter, this);
    g3.updateCallback = CC_CALLBACK_1(EnemyGroup::g3update, this);
    
    FSMState g12;
    g12.setName(GroupState::g12);
    g12.enterCallback = CC_CALLBACK_0(EnemyGroup::g12enter, this);
    g12.updateCallback = CC_CALLBACK_1(EnemyGroup::g12update, this);
    
    FSMState g111;
    g111.setName(GroupState::g111);
    g111.enterCallback = CC_CALLBACK_0(EnemyGroup::g111enter, this);
    g111.updateCallback = CC_CALLBACK_1(EnemyGroup::g111update, this);
    
    addState(g3);
    addState(g12);
    addState(g111);
    
    setNextState(GroupState::g3);
    
}

bool EnemyGroup::isAllTheSame(int from , int to , std::string fieldName ...){
    
    if (fieldName == "radius") {
        float r = _enemies.at(from)->getCurRadius();
        for (int i = from + 1 ; i <= to ; i ++) {
            if (_enemies.at(i)->getCurRadius() != r) {
                return false;
            }
        }
        return true;
    }else if (fieldName == "AttempToChange"){
        int attempToChange = _enemies.at(from)->getAttempToChange();
        for (int i = from + 1 ; i <= to ; i ++) {
            if (_enemies.at(i)->getAttempToChange() != attempToChange) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void EnemyGroup::g3enter(){
    _randSwitch = On;
}

void EnemyGroup::g3update(float d){
    
    int i;
    for (i = 0; i < _enemies.size(); i++) {
        if (_enemies.at(i)->getAttempToChange() != AttempTochange::CanSet) {
            break;
        }
    }
    if (i == _enemies.size()) {
        float num = rand_0_1();
        for (i = 0 ; i < _enemies.size(); i++) {
            int var = num < 1.5 ? AttempTochange::True : AttempTochange::False;
            _enemies.at(i)->setAttempToChange(var);
        }
    }
    
    if (_scorer->getCircleCount() >= 1) {
        bool equal = true;
        float r = _enemies.at(0)->getCurRadius();
        for (int i = 1 ; i < _enemies.size() ; i ++) {
            if (_enemies.at(i)->getCurRadius() != r) {
                equal = false;
                break;
            }
        }
        //if enemies radius is all equal then can not change track in order to change team state
        if (_enemies.at(0)->getAttempToChange() != AttempTochange::Disable && equal) {
            for (auto iter : _enemies) {
                iter->setAttempToChange(AttempTochange::Disable);
            }
        }
        if (_enemies.at(1)->isChangeToCircle() && _enemies.at(0)->getAttempToChange() == AttempTochange::Disable) {
            _delayedStateName = GroupState::g12;
        }
        
    }

}

void EnemyGroup::g12enter(){
    _randSwitch = Off;
    _enemies.at(1)->speedDown();
    _enemies.at(2)->speedDown();
    _timer = 0;
}

void EnemyGroup::g12update(float d){
    
    if (_randSwitch == On) {
        
        int i;
        for (i = 0; i < _enemies.size(); i++) {
            if (_enemies.at(i)->getAttempToChange() != AttempTochange::CanSet) {
                break;
            }
        }
        
    }else if ((_timer += d) >= TIME_FACTOR / _enemies.at(0)->getVelo()){
        _enemies.at(1)->speedResume();
        _enemies.at(2)->speedResume();
        //turn on the random change track
        _randSwitch = On;
    }
    
}

void EnemyGroup::g111enter(){
    
}

void EnemyGroup::g111update(float d){
    
}

cocos2d::Vector<Enemy *> * EnemyGroup::getEnemies(){
    return &_enemies;
}

void EnemyGroup::update(float d){
    FSM::update(d);
    for (auto iter : _enemies) {
        iter->update(d);
    }
}

void EnemyGroup::reset(){
    resetFSM();
    for(auto iter : _enemies){
        iter->reset();
    }
}

void EnemyGroup::addEnemy(Enemy *enemy){
    enemy->setGroup(this);
    _enemies.pushBack(enemy);
}



