//
//  Commander.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/29.
//
//

#include "Commander.hpp"
#include "Scorer.hpp"
#include "Controller.hpp"
#include "../Entity/Enemy.hpp"
#include "../utils/FSm/FSMState.h"
#include "../utils/Z_Math.h"

USING_NS_CC;

Commander::~Commander(){
    
}

Commander::Commander():
_timer(0),
_scorer(nullptr),
_randSwitch(RandSwitch::On){
    
}

bool Commander::init(){
    initFSM();
    _scorer = Controller::getInstance()->getScorer();
    return true;
}

void Commander::initFSM(){
    FSMState g3;
    g3.setName(GroupState::g3);
    g3.enterCallback = CC_CALLBACK_0(Commander::g3enter, this);
    g3.updateCallback = CC_CALLBACK_1(Commander::g3update, this);
    
    FSMState g12;
    g12.setName(GroupState::g12);
    g12.enterCallback = CC_CALLBACK_0(Commander::g12enter, this);
    g12.updateCallback = CC_CALLBACK_1(Commander::g12update, this);
    
    FSMState g111;
    g111.setName(GroupState::g111);
    g111.enterCallback = CC_CALLBACK_0(Commander::g111enter, this);
    g111.updateCallback = CC_CALLBACK_1(Commander::g111update, this);
    
    addState(g3);
    addState(g12);
    addState(g111);
    
    setNextState(GroupState::g3);
    
}

bool Commander::isAllTheSame(int from , int to , std::string fieldName ...){
    
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

void Commander::g3enter(){
    if (getPreviousStateName() != -1) {
        _enemies.at(2)->speedUp();
        _randSwitch = Off;
    }
}

void Commander::g3update(float d){
    
}

void Commander::g12enter(){
   
}

void Commander::g12update(float d){
    
    
}

void Commander::g111enter(){
    _randSwitch = Off;
    _enemies.at(2)->speedDown();
    for(auto iter : _enemies){
        iter->setAttempToChange(AttempToChange::CanSet);
    }
    _timer = 0;
}

void Commander::g111update(float d){
    
    
}

cocos2d::Vector<Enemy *> * Commander::getEnemies(){
    return &_enemies;
}

void Commander::update(float d){
    FSM::update(d);
    for (auto iter : _enemies) {
        iter->update(d);
    }
}

void Commander::reset(){
    resetFSM();
    for(auto iter : _enemies){
        iter->reset();
    }
}

void Commander::addEnemy(Enemy *enemy){
//    enemy->setGroup(this);
    enemy->setCommander(this);
    _enemies.pushBack(enemy);
}







