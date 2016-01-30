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
_randSwitch(true),
_enemies(nullptr),
_bFormated(true){
    
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
        
        float r = _enemies->at(from)->getCurRadius();
        for (int i = from ; i <= to ; i ++) {
            if (_enemies->at(i)->getCurRadius() != r) {
                ret = false;
                break;
            }
        }
    }else if (fieldName == "TrackState"){
        
        int tmp = va_arg(args , int) ;
        
        int trackState = tmp == -1 ? _enemies->at(from)->getTrackState() : tmp;
        for (int i = from ; i <= to ; i ++) {
            if (_enemies->at(i)->getTrackState() != trackState) {
                ret = false;
                break;
            }
        }
    }else if (fieldName == "UDLR"){
        
        int tmp = va_arg(args , int);
        
        int UDLR = tmp == -1 ? _enemies->at(from)->getUDLR() : tmp;
        for (int i = from ; i <= to ; i ++) {
            if (_enemies->at(i)->getUDLR() != UDLR) {
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
        _enemies->at(2)->speedUp();
        _randSwitch = false;
        _bFormated = false;
    }
    _timer = 0;
    _scorer->setCircleCount(0);
}

void Commander::g3update(float d){
    _timer += d;
    
    if (_randSwitch) {
        formation();
        if (_scorer->getCircleCount() >= 3) {
            _delayedStateName = g12;
        }
    }else if (_timer >= 2 * TIME_FACTOR / _enemies->at(0)->getVelo()){
        _enemies->at(1)->speedResume();
        _enemies->at(2)->speedResume();
        _randSwitch = true;
    }else if(_timer >= TIME_FACTOR / _enemies->at(0)->getVelo()){
        _enemies->at(1)->speedUp();
    }
}

void Commander::g12enter(){
    _randSwitch = false;
    _enemies->at(1)->speedDown();
    _enemies->at(2)->speedDown();
    _timer = 0;
}

void Commander::g12update(float d){
    
    if (_randSwitch) {
        if (_scorer->getCircleCount() >= 5) {
            _delayedStateName = g111;
        }
        return;
    }else if ((_timer += d) >= TIME_FACTOR / _enemies->at(0)->getVelo()){
        _enemies->at(1)->speedResume();
        _enemies->at(2)->speedResume();
        _randSwitch = true;
    }
    
}

void Commander::g111enter(){
    _randSwitch = false;
    _enemies->at(2)->speedDown();
    _timer = 0;
}

void Commander::formation(){
    if (!_bFormated) {
        if (isAllTheSame(0 , 2 , "UDLF" , UDLR::up)) {
            _bFormated = true;
            auto X = _enemies->at(2)->getPositionX();
            for (int i = 1 ; i > -1; i --) {
                _enemies->at(i)->setPositionX(X + 95 * (2 - i));
            }
        }else if (isAllTheSame(0 , 2 , "UDLF" , UDLR::up)){
            _bFormated = true;
            auto X = _enemies->at(2)->getPositionX();
            for (int i = 1 ; i > -1 ; i --) {
                _enemies->at(i)->setPositionX(X - 95 * (2 - i));
            }
        }
    }
}

void Commander::g111update(float d){
    
    if (_randSwitch) {
        if (_scorer->getCircleCount() >= 7) {
            _randSwitch = false;
            _enemies->at(1)->followHead();
            _enemies->at(2)->followHead();
            if (isAllTheSame(0 , 2, "radius") && isAllTheSame(0 , 1, "TrackState" , TrackState::Normal)) {
                _delayedStateName = g3;
                for(auto iter : * _enemies){
                    iter->setisChangeTrack(false);
                }
            }
        }
    }else if ((_timer += d) >= TIME_FACTOR / _enemies->at(0)->getVelo()){
        _enemies->at(2)->speedResume();
        _randSwitch = true;
    }
    
}

void Commander::update(float d){
    FSM::update(d);
}

void Commander::reset(){
    resetFSM();
}








