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
#include "SimpleAudioEngine.h"
USING_NS_CC;

MainUI::MainUI():
_over(nullptr),
_normal(nullptr),
_btnClose(nullptr),
_bCanClose(nullptr){
}

MainUI::~MainUI(){
    
}

bool MainUI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    if (Controller::getInstance()->getCurGameState() != GameState::GRunning) {
        return true;
    }
    Controller::getInstance()->getScorer()->getUserCar()->changeTrack();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/tap_2.mp3");

    return true;
}

void MainUI::playRewardEff(){
    _normal->playRewardEff();
}

void MainUI::initCloseButton(){
    GET_CENTER_WINSIZE
    _btnClose = ui::Button::create("img/03.png");
    _btnClose->setPosition(Vec2(winSize.width * 0.05, winSize.height * 0.93));
    addChild(_btnClose);
    _btnClose->addClickEventListener(CC_CALLBACK_0(MainUI::onCloseClick, this));
    
}

void MainUI::onCloseClick(){
    Director::getInstance()->end();
    CocosDenshion::SimpleAudioEngine::getInstance()->end();
    auto confirm = Label::createWithTTF("" , "fonts/Marker Felt.ttf" , 60);
//    Controller::destroyInstance();
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
        
        initCloseButton();
        
        _normal->pop();
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(MainUI::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


