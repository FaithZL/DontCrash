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
#include "Z_Math.h"

USING_NS_CC;

Group::Group():
_bCanSwitch(false),
_scorer(nullptr){
    
}

Group::~Group(){
    
}

bool Group::init(){
    initFSM();
    return true;
}

void Group::initFSM(){
    FSMState g3;
    g3.setName(EnemyState::g3);
    g3.enterCallback = CC_CALLBACK_0(Group::g3enter, this);
    g3.updateCallback = CC_CALLBACK_1(Group::g3update, this);
    
    FSMState g12;
    g12.setName(EnemyState::g12);
    g12.enterCallback = CC_CALLBACK_0(Group::g12enter, this);
    g12.updateCallback = CC_CALLBACK_1(Group::g12update, this);
    
    FSMState g111;
    g111.setName(EnemyState::g111);
    g111.enterCallback = CC_CALLBACK_0(Group::g111enter, this);
    g111.updateCallback = CC_CALLBACK_1(Group::g111update, this);
    
    addState(g3);
    addState(g12);
    addState(g111);
    
    setNextState(EnemyState::g3);
    
}

float Group::getDistanceInTrack(Enemy * front , Enemy * back){
    auto fPos = front->getPosition();
    auto bPos = back->getPosition();
    auto radius = front->getCurRadius();
    auto circumference = 2 * (POS_R.x - POS_L.x) + 2 * PI * radius;
    
    if (front->getUDLR() == left) {
        
        auto fAngle = getAngle(POS_L , fPos);
        
        if (back->getUDLR() == up) {
            
            return circumference - (radius * (fAngle - PI / 2) + (bPos.x - POS_L.x));
            
        }else if (back->getUDLR() == left){
            
            auto arc = fabs((fAngle - getAngle(POS_L, bPos)) * radius);
            
            return (fPos.y > bPos.y) ? arc : circumference - arc;
        
        }else if (back->getUDLR() == down){
        
            return (bPos.x - POS_L.x) + radius * (1.5 * PI - fAngle);
            
        }else if (back->getUDLR() == right){
            
            auto bAngle = getAngle(POS_R, bPos);
            
            if (bAngle < PI / 2) {
                bAngle = bAngle + PI / 2;
            }else{
                bAngle = bAngle - 1.5 * PI;
            }
            
            return (1.5 * PI - fAngle + bAngle) * radius + (POS_R.x - POS_L.x);
            
        }
        
    }else if (front->getUDLR() == right){
        
        auto fAngle = getAngle(POS_R , fPos);
        
        if (back->getUDLR() == left) {
            
            return circumference - getDistanceInTrack(back, front);
        
        }else if (back->getUDLR() == right){
            
            auto bAngle = getAngle(POS_R , bPos);
            
            if (bAngle > 1.5 * PI) {
                bAngle = bAngle - 1.5 * PI;
            }else{
                bAngle = bAngle + PI / 2;
            }
            
            if (fAngle > 1.5 * PI) {
                fAngle = fAngle - 1.5 * PI;
            }else{
                fAngle = fAngle + PI / 2;
            }
            
            auto arc = fabs(radius * (bAngle - fAngle));
            
            return (fPos.y < bPos.y) ? arc : circumference - arc;
            
        }else if (back->getUDLR() == up){
            
            if (fAngle > 1.5 * PI) {
                fAngle = PI * 2.5 - fAngle;
            }else{
                fAngle = PI / 2 - fAngle;
            }
            
            return (POS_R.x - bPos.x) + fAngle * radius;
            
        }else if (back->getUDLR() == down){
            
            if (fAngle > 1.5 * PI) {
                fAngle = fAngle - 1.5 * PI;
            }else{
                fAngle = fAngle + PI / 2;
            }
            
            return circumference - ((POS_R.x - bPos.x) + fAngle * radius);
            
        }
        
    }else if (front->getUDLR() == up){
        
        if (back->getUDLR() == up) {
            
            auto d = fabs(fPos.x - bPos.x);
            
            return (fPos.x > bPos.x) ? d : circumference - d;
            
        }else if (back->getUDLR() == down){
            
            return (fPos.x - POS_L.x) + (bPos.x - POS_L.x) + PI * radius;
            
        }else if (back->getUDLR() == left){
            
            return circumference - getDistanceInTrack(back, front);
            
        }else if (back->getUDLR() == right){
            
            return circumference - getDistanceInTrack(back, front);
            
        }
        
    }else if (front->getUDLR() == down){
        
        if (back->getUDLR() == down) {
            
            auto d = fabs(fPos.x - bPos.x);
            
            return (fPos.x < bPos.x) ? d : circumference - d;
        
        }else if (back->getUDLR() == up){
            
            return circumference - getDistanceInTrack(back , front);
            
        }else if (back->getUDLR() == left){
            
            return circumference - getDistanceInTrack(back , front);
            
        }else if (back->getUDLR() == right){
            
            return circumference - getDistanceInTrack(back , front);
            
        }
        
    }
    return -1;
}

void Group::g3enter(){
    
}

void Group::g3update(float d){
    
    
//    int i;
//    for (i = 0; i < _enemies.size(); i++) {
//        if (_enemies.at(i)->getAttempToChange() != AttempTochange::CanSet) {
//            break;
//        }
//    }
//    if (i == _enemies.size()) {
//        float num = rand_0_1();
//        for (i = 0 ; i < _enemies.size(); i++) {
//            int var = num < 0.5 ? AttempTochange::True : AttempTochange::False;
//            _enemies.at(i)->setAttempToChange(var);
//        }
//    }
    
//    if (_scorer->getCircleCount() >= 0 && _enemies.at(1)->isChangeToCircle()) {
//        
//        _delayedStateName = EnemyState::g12;
//        
//    }
}

void Group::g12enter(){
//    _enemies.at(1)->speedDown();
//    _enemies.at(2)->speedDown();
    
}
static float testCount = 0;
void Group::g12update(float d){
    
//    if (getDistanceInTrack(_enemies.at(0), _enemies.at(1)) >= 390) {
//        _enemies.at(1)->speedResume();
//        _enemies.at(2)->speedResume();
//        
//    }
    if (_enemies.at(1)->getUDLR() == right) {
        _enemies.at(1)->setVelo(0 , true);
    }
    
    
//    auto nowd = getDistanceInTrack(_enemies.at(0), _enemies.at(1));
//    CCLOG("%f" , nowd);
//    if (nowd == testCount) {
//        CCLOG("prePos : %f , %f" , _enemies.at(0)->getPrePos().x , _enemies.at(1)->getPrePos().y);
//        CCLOG("curPos : %f , %f" , _enemies.at(0)->getPositionX() , _enemies.at(1)->getPositionY());
////        Director::getInstance()->pause();
//    }
//
//    testCount = nowd;
}

void Group::g111enter(){
    
}

void Group::g111update(float d){
    
}

cocos2d::Vector<Enemy *> * Group::getEnemies(){
    return &_enemies;
}

void Group::update(float d){
    FSM::update(d);
    for (auto iter : _enemies) {
        iter->update(d);
    }
}

void Group::reset(){
    _delayedStateName = EnemyState::g3;
    for(auto iter : _enemies){
        iter->reset();
    }
}

void Group::addEnemy(Enemy *enemy){
    enemy->setGroup(this);
    _enemies.pushBack(enemy);
}



