//
//  Scorer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/22.
//
//

#include "Scorer.hpp"
#include "Enemy.hpp"
#include "Car.hpp"

USING_NS_CC;

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

bool Scorer::isCollision(){
    for(auto &it : * _enemies){
        if (it->getCurRadius() == _car->getCurRadius() || it->getTrackState() == TrackState::ToInner || it->getTrackState() == TrackState::ToOuter) {
            if (isIntersect(_car, it)) {
                _car->blast();
                it->blast();
                return true;
            }
        }
    }
    return false;
}

bool Scorer::isIntersect(cocos2d::Node * node1, cocos2d::Node * node2){
    auto size1 = node1->getContentSize();
    auto pos1 = node1->getPosition();
    auto rect1 = Rect(pos1.x - size1.width / 2 , pos1.y - size1.height / 2 , size1.width, size1.height);
    auto size2 = node2->getContentSize();
    auto pos2 = node2->getPosition();
    auto rect2 = Rect(pos2.x - size2.width / 2 , pos2.y - size2.height / 2 , size2.width, size2.height);
    
    if (rect2.intersectsRect(rect1)) {
        return true;
    }
    return false;
}

void Scorer::setCars(Car * car, cocos2d::Vector<Enemy *> * enemies){
    _car = car;
    _enemies = enemies;
    _enemies->swap(0, 2);
}

void Scorer::update(float d){
    
}

