//
//  Controller.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Controller.hpp"
#include "Car.hpp"
#include "Enemy.hpp"
#include "GameLayer.hpp"
#include "UILayer.hpp"
#include "Scorer.hpp"
#include "Signal.hpp"
#include "Group.hpp"

USING_NS_CC;

Controller * Controller::s_pController = nullptr;

Controller::Controller():
_scheduler(nullptr),
_uiLayer(nullptr),
_gameLayer(nullptr),
_scorer(nullptr),
_signal(nullptr)
{
    
}

Controller::~Controller()
{
    CC_SAFE_DELETE(_gameLayer);
    CC_SAFE_DELETE(_uiLayer);
    CC_SAFE_DELETE(_scorer);
}

Controller * Controller::getInstance()
{
    if (!s_pController) {
        s_pController = new (std::nothrow)Controller();
        s_pController->init();
    }
    return s_pController;
}

bool Controller::init()
{
    _scheduler = Director::getInstance()->getScheduler();
    _scorer = Scorer::create();
    CC_SAFE_RETAIN(_scorer);
    _signal = Signal::create();
    CC_SAFE_RETAIN(_signal);
    return true;
}


void Controller::start()
{
    auto group = _scorer->getGroup();
    auto _enemies = group->getEnemies();
    for(auto iter : * _enemies){
        CCLOG("%d , %f , %f" , iter->getTag() , iter->getPositionX() , iter->getPositionY());
    }
    scheduleUpdate();
}

cocos2d::Scene * Controller::createScene()
{
    Scene * ret = Scene::create();
    _gameLayer = GameLayer::create();
    _uiLayer = UILayer::create();
    ret->addChild(_gameLayer);
    ret->addChild(_uiLayer);
    return ret;
}

void Controller::over(){
    _uiLayer->translateToState(GameState::GOver);
}

void Controller::update(float d)
{
    if (_scorer->isCollision()) {
        pause();
        over();
        return;
    }
    _scorer->update(d);
}

void Controller::scheduleUpdate()
{
    _scheduler->scheduleUpdate(this, 0, false);
}

void Controller::unscheduleUpdate()
{
    _scheduler->unscheduleUpdate(this);
}

void Controller::reset()
{
    _scorer->reset();
    _uiLayer->reset();
}

void Controller::pause()
{
    unscheduleUpdate();
}



