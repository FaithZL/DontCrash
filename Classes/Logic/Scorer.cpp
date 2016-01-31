//
//  Scorer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/22.
//
//

#include "Scorer.hpp"

#include "../Entity/Enemy.hpp"
#include "../Entity/Car.hpp"
#include "../constant.h"
#include "Controller.hpp"
#include "../utils/Signal.hpp"
#include "Commander.hpp"
#include "../Data/UserData.hpp"
#include "SimpleAudioEngine.h"
#include "../View/MainUI.hpp"

USING_NS_CC;

Scorer::Scorer():
_car(nullptr),
_score(0),
_circleCount(0){
    
}

Scorer::~Scorer(){
    
}

bool Scorer::init(){
    return true;
}


void Scorer::playRewardEff(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/perfect.mp3");
    Controller::getInstance()->getMainUI()->playRewardEff();
}

void Scorer::reset(){
    if (_car) {
        _car->reset();
    }
    for(auto iter : _enemies){
        iter->reset();
    }
    _score = 0;
    _circleCount = 0;
    Controller::getInstance()->getSignal()->dispatchEvent(ON_SCORE_CHANGE , _score);
}

void Scorer::isSupassBest(){
    auto userData = Controller::getInstance()->getUserData();
    if (_score > userData->getBestScore()) {
        userData->setBestScore(_score);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/NewHigh.mp3");
    }
}

void Scorer::checkMeet(Car *car, Enemy *enemy){
    
    if (isMeet(car , enemy)) {
        switch (enemy->getTag()) {
            case 0:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/point01.mp3");
                break;
                
            case 1:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/point02.mp3");
                break;
                
            case 2:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/point03.mp3");
                break;
                
            default:
                break;
        }
        _score ++;
    }else{
        return;
    }
    if (car->getExtraScoreByTag(enemy->getTag()) > 0) {
        _score ++;
        playRewardEff();
    }
    isSupassBest();
    Controller::getInstance()->getSignal()->dispatchEvent(ON_SCORE_CHANGE , _score);
}

void Scorer::checkSameTrack(){
    for (int i = 0 ; i < _enemies.size() ; i ++) {
        auto enemy = _enemies.at(i);
        if (_car->getCurRadius() == enemy->getCurRadius()) {
            _car->setExtraScoreByTag(enemy->getTag());
        }
    }
}

void Scorer::addEnemy(Enemy *enemy){
    _enemies.pushBack(enemy);
}

Vector<Enemy *> * Scorer::getEnemies(){
    return &_enemies;
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
    for(auto iter : _enemies){
        iter->update(d);
    }
    scoring(d);
    recordCircleCount(d);
    checkSameTrack();
    
}

void Scorer::scoring(float d){
    Commander * commander = Controller::getInstance()->getCommander();
    
    switch (commander->getCurrentStateName()) {
        case GroupState::g3:
            checkMeet(_car , _enemies.at(0));
            break;
            
        case GroupState::g12:
            checkMeet(_car , _enemies.at(0));
            checkMeet(_car , _enemies.at(1));
            break;
            
        case GroupState::g111:
            for (auto i = 0; i < _enemies.size(); i ++) {
                checkMeet(_car, _enemies.at(i));
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

void Scorer::difficultyUp(){
    _car->difficultyUp();
    for(auto iter : _enemies){
        iter->difficultyUp();
    }
}

void Scorer::relieve(){
    _car->relieve();
    for(auto iter : _enemies){
        iter->relieve();
    }
}

bool Scorer::isCollision(){
    for(auto &it : _enemies){
        if (it->getCurRadius() == _car->getCurRadius() || it->getTrackState() != TrackState::Normal || _car->getTrackState() != TrackState::Normal) {
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


