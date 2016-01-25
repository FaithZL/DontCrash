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
_enemyState(EnemyState::g3){
    
}

Group::~Group(){
    
}

bool Group::init(){
    return true;
}

void initFSM(){
    
}

cocos2d::Vector<Enemy *> * Group::getEnemies(){
    return &_enemies;
}

void Group::randonChangeTrack(float d){
    switch (_enemyState) {
        case EnemyState::g3:
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
            break;
            
        case EnemyState::g12:
            
            break;
            
        case EnemyState::g111:
            
            break;
            
        default:
            break;
    }
    
}


void Group::controlEnemyState(float d , int score){
    int div = score / 40;
    int mod = score % 40;
    if (mod < 8 && _bCanSwitch) {
        //switch to 3 formation
        _bCanSwitch = false;
        
    }else if (mod < 19 && _bCanSwitch) {
        //switch to 1 and 2 formation
        _bCanSwitch = false;
        
    }else if (_bCanSwitch){
        //switch to 1 and 1 and 1 formation
        _bCanSwitch = false;
        
    }
    
}

void Group::update(float d){
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



