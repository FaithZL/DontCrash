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
#include "../constant.h"
#include "../utils/Signal.hpp"
#include "../Logic/Scorer.hpp"
#include "OverLayer.hpp"
#include "NormalLayer.hpp"
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
        return true;
    }
    Controller::getInstance()->getScorer()->getUserCar()->changeTrack();
    
    return true;
}

void MainUI::reset(){
    _over->pickUp();
    _normal->pop();
}

void MainUI::over(){
    _normal->pickUp();
    _over->pop();
}

bool MainUI::init(){
    if (Layer::init()) {
        
        _normal = NormalLayer::create();
        addChild(_normal);
        _over = OverLayer::create();
        addChild(_over);
        
        _normal->pop();
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(MainUI::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


