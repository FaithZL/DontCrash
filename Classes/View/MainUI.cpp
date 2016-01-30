//
//  MainUI.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "MainUI.hpp"
#include "../Logic/Controller.hpp"
#include "../Entity/Car.hpp"
#include "../Entity/Enemy.hpp"
#include "../constant.h"
#include "../utils/FSM/FSMState.h"
#include "../utils/Signal.hpp"
#include "../Logic/Scorer.hpp"
USING_NS_CC;

MainUI::MainUI():
_over(nullptr),
_normal(nullptr){
}

MainUI::~MainUI()
{
    
}

bool MainUI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    if (Controller::getInstance()->getCurGameState() != GameState::GRunning) {
        return false;
    }
    Controller::getInstance()->getScorer()->getUserCar()->changeTrack();
    
    return true;
}




void MainUI::reset(){
    
}


bool MainUI::init(){
    if (Layer::init()) {
        
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(MainUI::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


