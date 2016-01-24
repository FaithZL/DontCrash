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
#include "constant.h"
#include "Controller.hpp"
#include "Signal.hpp"

USING_NS_CC;

Scorer::Scorer():
_car(nullptr),
_score(0),
_enemies(nullptr),
_enemyState(EnemyState::g3){
    
}

Scorer::~Scorer(){
    
}

bool Scorer::init(){
    return true;
}

void Scorer::refreshScore(){
    std::string on = "onScoreChange";
    Controller::getInstance()->getSignal()->dispatchEvent(on , _score);
}

void Scorer::playRewardEff(){
    
}

void Scorer::checkMeet(Car *car, Enemy *enemy){
    
    if (isMeet(car , enemy)) {
        switch (enemy->getTag()) {
            case 0:
                
                break;
                
            case 1:
                
                break;
                
            case 2:
                
                break;
            default:
                break;
        }
        CCLOG("%d" , enemy->getTag());
        _score ++;
    }else{
        return;
    }
    if (car->getExtraScoreByTag(enemy->getTag()) > 0) {
        _score ++;
        playRewardEff();
    }
    refreshScore();
}

void Scorer::checkSameTrack(){
    for (int i = 0 ; i < _enemies->size() ; i ++) {
        auto enemy = _enemies->at(i);
        if (_car->getCurRadius() == enemy->getCurRadius()) {
            _car->setExtraScoreByTag(enemy->getTag());
        }
    }
}

bool Scorer::isMeet(Car *car, Enemy *enemy){
    auto ret = false;
    
    auto carPos = car->getPosition();
    auto enemyPos = enemy->getPosition();
    auto distance = (carPos - enemyPos).length();
    auto tag = enemy->getTag();
    auto preDis = car->getPreDistance(tag);
    
    if (distance > preDis && preDis >= R_OUTER - R_INNER && preDis < R_INNER * 2 && car->getFarthestFlagbyTag(tag)) {
        car->setFarthestFlagbyTag(tag , false);
        ret = true;
    }
    if (distance < preDis) {
        car->setFarthestFlagbyTag(tag, true);
    }
    car->setDistance(tag , distance);
    
    return ret;
}

void Scorer::update(float d){
    scoring(d);
    checkSameTrack();
}

void Scorer::scoring(float d){
    
    
    switch (_enemyState) {
        case EnemyState::g3:
            checkMeet(_car , _enemies->at(0));
            break;
            
        case EnemyState::g12:
            checkMeet(_car , _enemies->at(0));
            checkMeet(_car , _enemies->at(1));
            break;
            
        case EnemyState::g111:
            for (auto i = 0; i < _enemies->size(); i ++) {
                checkMeet(_car, _enemies->at(i));
            }
            break;
        default:
            break;
    }
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
}



