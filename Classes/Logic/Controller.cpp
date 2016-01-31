//
//  Controller.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Controller.hpp"
#include "../Entity/Car.hpp"
#include "../Entity/Enemy.hpp"
#include "../View/GameLayer.hpp"
#include "../View/MainUI.hpp"
#include "Scorer.hpp"
#include "../utils/Signal.hpp"
#include "Commander.hpp"
#include "../Data/UserData.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Controller * Controller::s_pController = nullptr;

Controller::Controller():
_scheduler(nullptr),
_mainUI(nullptr),
_gameLayer(nullptr),
_scorer(nullptr),
_signal(nullptr),
_userData(nullptr){
    
}

Controller::~Controller(){
//    CC_SAFE_DELETE(_gameLayer);
//    CC_SAFE_DELETE(_mainUI);
    CC_SAFE_RELEASE(_scorer);
    CC_SAFE_RELEASE(_signal);
    CC_SAFE_RELEASE(_userData);
}

Controller * Controller::getInstance()
{
    if (!s_pController) {
        s_pController = new (std::nothrow)Controller();
        s_pController->init();
    }
    return s_pController;
}

void Controller::destroyInstance(){
    s_pController->release();
    s_pController = nullptr;
}

bool Controller::init()
{
    _scheduler = Director::getInstance()->getScheduler();
    _scorer = Scorer::create();
    CC_SAFE_RETAIN(_scorer);
    _signal = Signal::create();
    CC_SAFE_RETAIN(_signal);
    _commander = Commander::create();
    CC_SAFE_RETAIN(_commander);
    _commander->setScorer(_scorer);
    _userData = UserData::create();
    CC_SAFE_RETAIN(_userData);
    autorelease();
    retain();
    return true;
}


void Controller::start()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/start.mp3");
    std::function<void(float)> callback = [this](float d){
        scheduleUpdate();
        _gameState = GRunning;
    };
    
    scheduleOnce(callback, 0.3f , "start");
}

void Controller::scheduleOnce(std::function<void(float)> &callback, float delay , std::string key){
    
    _scheduler->schedule(callback , this, 0 , 0 , delay , false , key);
    
}

cocos2d::Scene * Controller::createScene()
{
    Scene * ret = Scene::create();
    _gameLayer = GameLayer::create();
    _mainUI = MainUI::create();
    ret->addChild(_gameLayer);
    ret->addChild(_mainUI , 100);
    return ret;
}

void Controller::update(float d){
    _scorer->testAuto();
    if (_scorer->isCollision()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/crash.mp3");
        stop();
        return;
    }
    _scorer->update(d);
    _commander->update(d);
}

void Controller::scheduleUpdate(){
    _scheduler->scheduleUpdate(this, 0, false);
}

void Controller::unscheduleUpdate(){
    _scheduler->unscheduleUpdate(this);
}

void Controller::reset(){
    _scorer->reset();
    _mainUI->reset();
    _commander->reset();
}

void Controller::pause(){
    unscheduleUpdate();
    _gameState = GPause;
}

void Controller::resume(){
    scheduleUpdate();
    _gameState = GRunning;
}

void Controller::stop(){
    unscheduleUpdate();
    _mainUI->over();
    _gameState = GOver;
}



