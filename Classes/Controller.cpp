//
//  Controller.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "Controller.hpp"
#include "Car/Car.hpp"
#include "Enemy.hpp"
#include "GameLayer.hpp"
#include "UILayer.hpp"

USING_NS_CC;

Controller * Controller::s_pController = nullptr;

Controller::Controller():
_car(nullptr),
_scheduler(nullptr),
_uiLayer(nullptr),
_gameLayer(nullptr),
_score(0)
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
    return true;
}

void Controller::addEnemy(Enemy * enemy)
{
    _enemies.pushBack(enemy);
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

bool Controller::isCollision(cocos2d::Node * node1, cocos2d::Node * node2){
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

void Controller::doPerFrame(float d)
{
    for(auto &it : _enemies){
        if (it->getCurRadius() == _car->getCurRadius() || it->getChangeTrackState() == ChangeState::ToInner || it->getChangeTrackState() == ChangeState::ToOuter) {
            if (isCollision(_car, it)) {
                _car->blast();
                it->blast();
                pause();
                break;
            }
        }
    }
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
    doPerFrame(d);
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
}

void Controller::pause()
{
    unscheduleUpdate();
}



