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

Controller * Controller::s_pController = nullptr;

Controller::Controller():
_car(nullptr)
{
    
}

Controller::~Controller()
{
    CC_SAFE_DELETE(_car);
    for(auto &it : _enemies)
    {
        CC_SAFE_DELETE(it);
    }
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
    _car->start();
    for(auto &it : _enemies)
    {
        it->start();
    }
}

void Controller::reset()
{
    _car->reset();
    for(auto &it : _enemies)
    {
        it->reset();
    }
}

void Controller::pause()
{
    _car->pause();
    for(auto &it : _enemies)
    {
        it->pause();
    }
}



