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

USING_NS_CC;

Controller * Controller::s_pController = nullptr;

Controller::Controller():
_car(nullptr),
_scheduler(nullptr),
_uiLayer(nullptr),
_gameLayer(nullptr),
_scorer(nullptr)
{
    
}

Controller::~Controller()
{
    CC_SAFE_DELETE(_car);
    for(auto &it : _enemies)
    {
        CC_SAFE_DELETE(it);
    }
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
    _scorer->retain();
    return true;
}

void Controller::addEnemy(Enemy * enemy)
{
    _enemies.pushBack(enemy);
}

void Controller::initScorer(){
    _scorer->setCars(_car, &_enemies);
}

cocos2d::Vector<Enemy *> * Controller::getEnemies()
{
    return &_enemies;
}

void Controller::start()
{
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
    if (_car) {
        _car->update(d);
    }
    for(auto &it : _enemies)
    {
        it->update(d);
    }
    
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
    if (_car) {
        _car->reset();
    }
    for(auto &it : _enemies)
    {
        it->reset();
    }
    _uiLayer->translateToState(GameState::GNormal);
}

void Controller::pause()
{
    unscheduleUpdate();
}



