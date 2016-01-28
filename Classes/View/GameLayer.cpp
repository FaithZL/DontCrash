//
//  GameLayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "GameLayer.hpp"
#include "Car.hpp"
#include "constant.h"
#include "Controller.hpp"
#include "Enemy.hpp"
#include "Scorer.hpp"
#include "EnemyGroup.hpp"

USING_NS_CC;

GameLayer::GameLayer()
{
    
}

GameLayer::~GameLayer()
{
    
}

bool GameLayer::init()
{
    if (Layer::init()) {
        _bg = Sprite::create("img/bg.png");
        _bg2 = Sprite::create("img/bg2.png");
        _track = Sprite::create("img/track.png");
        
        auto winSize = Director::getInstance()->getWinSize();
        
        auto size = Director::getInstance()->getVisibleSize();
        
        _track->setPosition(Vec2(size.width / 2 , size.height / 2));
        _bg->setPosition(Vec2(size.width / 2 , size.height / 2));
        _bg2->setPosition(Vec2(size.width / 2 , size.height / 2));
        addChild(_bg);
        addChild(_bg2);
        addChild(_track);
        
        srand(time(NULL));

        int d = 50;
        
        float X = winSize.width / 2 - 50;
        
        Vec2 pos = Vec2(X - d , POS_R.y + R_OUTER);
        auto car = Car::create("img/car.png", 700, pos, Direction::CCW);
        car->setBlastRes("img/zha.png");
        addChild(car , 100);
        Controller::getInstance()->getScorer()->setUserCar(car);
        
        for (int i = 0 ; i < 3; i++) {
            int l = 95;
            auto enemy = Enemy::create("img/car2.png", 700, Vec2(POS_R.x - 50 - l * i, POS_R.y + R_OUTER), Direction::CW);
            enemy->setTag(i);
            enemy->setBlastRes("img/zha2.png");
            Controller::getInstance()->getScorer()->getEnemyGroup()->addEnemy(enemy);
            addChild(enemy);
        }
        
        return true;
    }
    return false;
}







