//
//  Scoring.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/22.
//
//

#include "Scorer.hpp"

Scorer::Scorer():
_car(nullptr),
_score(0),
_enemies(nullptr){
    
}

Scorer::~Scorer(){
    
}

bool Scorer::init(){
    return true;
}

void Scorer::setCars(Car * car, cocos2d::Vector<Enemy *> * enemies){
    _car = car;
    _enemies = enemies;
    _enemies->swap(0, 2);
}

void Scorer::update(float d){
    _enemies ++;
    _enemies--;
    int i = 5;
}

