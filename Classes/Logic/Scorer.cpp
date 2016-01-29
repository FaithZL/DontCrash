//
//  Scorer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/22.
//
//

#include "Scorer.hpp"

#include "../Entity/Enemy.hpp"
#include "EnemyGroup.hpp"
#include "../Entity/Car.hpp"
#include "../constant.h"
#include "Controller.hpp"
#include "../utils/Signal.hpp"

USING_NS_CC;

Scorer::Scorer():
_car(nullptr),
_score(0),
_circleCount(0),
_enemies(nullptr),
_enemyGroup(nullptr){
    
}

Scorer::~Scorer(){
    
}

bool Scorer::init(){
    _enemyGroup = EnemyGroup::create();
    CC_SAFE_RETAIN(_enemyGroup);
    _enemyGroup->setScorer(this);
    _enemies = _enemyGroup->getEnemies();
    return true;
}


void Scorer::playRewardEff(){
    
}

void Scorer::reset(){
    if (_car) {
        _car->reset();
    }
    _enemyGroup->reset();
    _score = 0;
    _circleCount = 0;
    Controller::getInstance()->getSignal()->dispatchEvent("onScoreChange",_score);
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
//        CCLOG("%d" , enemy->getTag());
        _score ++;
    }else{
        return;
    }
    if (car->getExtraScoreByTag(enemy->getTag()) > 0) {
        _score ++;
        playRewardEff();
    }
    Controller::getInstance()->getSignal()->dispatchEvent("onScoreChange" , _score);
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
    
    if (distance < preDis && preDis >= 2 * R_INNER) {
        car->setFarthestFlagbyTag(tag, true);
    }
    car->setDistance(tag , distance);
    
    return ret;
}

void Scorer::update(float d){
    if (_car) {
        _car->update(d);
    }
//    _enemyGroup->update(d);
    scoring(d);
    recordCircleCount(d);
    checkSameTrack();
    
}

void Scorer::scoring(float d){
    
    
    switch (_enemyGroup->getCurrentStateName()) {
        case GroupState::g3:
            checkMeet(_car , _enemies->at(0));
            break;
            
        case GroupState::g12:
            checkMeet(_car , _enemies->at(0));
            checkMeet(_car , _enemies->at(1));
            break;
            
        case GroupState::g111:
            for (auto i = 0; i < _enemies->size(); i ++) {
                checkMeet(_car, _enemies->at(i));
            }
            break;
        default:
            break;
    }
}
 int test = 0;
void Scorer::recordCircleCount(float d){
    
    float originX = _car->getOriginPos().x;
    
    if (originX < _car->getPrePos().x && originX >= _car->getPositionX()) {
        _circleCount ++;
        test ++;
        CCLOG(" %d  circle" , test);
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


