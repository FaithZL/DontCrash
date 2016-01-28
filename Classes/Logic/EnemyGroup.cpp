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
_randSwitch(RandSwitch::On){
    
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
    
    va_list args;
    va_start(args, fieldName);
    
    bool ret = true;

    if (fieldName == "radius") {
        
        float r = _enemies.at(from)->getCurRadius();
        for (int i = from ; i <= to ; i ++) {
            if (_enemies.at(i)->getCurRadius() != r) {
                ret = false;
                break;
            }
        }
    }else if (fieldName == "AttempToChange"){
        
        int tmp = va_arg(args , int) ;
        
        int AttempToChange = tmp == -1 ? _enemies.at(from)->getAttempToChange() : tmp;
        for (int i = from + 1 ; i <= to ; i ++) {
            if (_enemies.at(i)->getAttempToChange() != AttempToChange) {
                ret = false;
                break;
            }
        }
    }
    va_end(args);
    return ret;
}

void EnemyGroup::g3enter(){
    if (getPreviousStateName() != -1) {
        _enemies.at(2)->speedUp();
        _randSwitch = Off;
    }
    _scorer->setCircleCount(0);
    for(auto iter : _enemies){
        iter->setAttempToChange(AttempToChange::CanSet);
    }
    _timer = 0;
}

void EnemyGroup::g3update(float d){
    _timer += d;
    if (_randSwitch == On) {
        if (isAllTheSame(0 , 2 , "AttempToChange" , AttempToChange::CanSet)) {
            float num = rand_0_1();
            for (int i = 0 ; i < _enemies.size(); i++) {
                int var = num < CHANGE_PROB ? AttempToChange::True : AttempToChange::False;
                _enemies.at(i)->setAttempToChange(var);
            }
        }
        if (_scorer->getCircleCount() >= 3) {
            if (isAllTheSame(0 , 2 , "radius")) {
                for (auto iter : _enemies) {
                    iter->setAttempToChange(AttempToChange::Disable);
                }
            }
            if (_enemies.at(1)->isChangeToCircle() && _enemies.at(0)->getAttempToChange() == AttempToChange::Disable) {
                _delayedStateName = GroupState::g12;
            }
            
        }
    }else if (_timer >= 2 * TIME_FACTOR / _enemies.at(0)->getVelo()){
        _enemies.at(1)->speedResume();
        _enemies.at(2)->speedResume();
        _randSwitch = On;
    }else if(_timer>= TIME_FACTOR / _enemies.at(0)->getVelo()){
        _enemies.at(1)->speedUp();
    }

}

void EnemyGroup::g12enter(){
    _randSwitch = Off;
    _enemies.at(1)->speedDown();
    _enemies.at(2)->speedDown();
    for(auto iter : _enemies){
        iter->setAttempToChange(AttempToChange::CanSet);
    }
    _timer = 0;
}

void EnemyGroup::g12update(float d){
    
    if (_randSwitch == On) {
        
        if (isAllTheSame(1 , 2 , "AttempToChange" , AttempToChange::CanSet)) {
            float num = rand_0_1();
            _enemies.at(1)->setAttempToChange(num < CHANGE_PROB ? AttempToChange::True : AttempToChange::False);
            _enemies.at(2)->setAttempToChange(num < CHANGE_PROB ? AttempToChange::True : AttempToChange::False);
        }
        _enemies.at(0)->setAttempToChange(rand_0_1() < CHANGE_PROB ? AttempToChange::True:AttempToChange::False);
        
        if (_scorer->getCircleCount() >= 5) {
            if (_enemies.at(1)->getCurRadius() == _enemies.at(2)->getCurRadius()) {
                _enemies.at(1)->setAttempToChange(AttempToChange::Disable);
                _enemies.at(2)->setAttempToChange(AttempToChange::Disable);
            }
            if (_enemies.at(1)->getAttempToChange() == AttempToChange::Disable && _enemies.at(2)->isChangeToCircle()) {
                _delayedStateName = GroupState::g111;
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
    _randSwitch = Off;
    _enemies.at(2)->speedDown();
    for(auto iter : _enemies){
        iter->setAttempToChange(AttempToChange::CanSet);
    }
    _timer = 0;
}

void EnemyGroup::g111update(float d){
    
    
    if (_randSwitch == On) {
       
        if (_scorer->getCircleCount() >= 7) {
            //Unified track
            if (_enemies.at(0)->getTrackState() == TrackState::Normal) {
                _enemies.at(0)->setAttempToChange(AttempToChange::Disable);
                for (int i = 1 ; i < _enemies.size() ; i++) {
                    if (_enemies.at(i)->getCurRadius() != _enemies.at(0)->getCurRadius()) {
                        _enemies.at(i)->setAttempToChange(AttempToChange::True);
                    }else{
                        _enemies.at(i)->setAttempToChange(AttempToChange::Disable);
                    }
                }
            }
            if (isAllTheSame(0 , 2 , "radius") && isAllTheSame(0 , 2, "AttempToChange" , AttempToChange::Disable)) {
                //change group state
                _delayedStateName = GroupState::g3;
            }
            
        }else{
            for(auto iter : _enemies){
                iter->setAttempToChange(rand_0_1() < CHANGE_PROB ? AttempToChange::True : AttempToChange::False);
            }
        }
        
    }else if ((_timer += d) >= TIME_FACTOR / _enemies.at(1)->getVelo()){
        _enemies.at(2)->speedResume();
        //turn on the random change track
        _randSwitch = On;
    }
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



