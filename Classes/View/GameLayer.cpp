//
//  GameLayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "GameLayer.hpp"
#include "../Entity/Car.hpp"
#include "../constant.h"
#include "../Logic/Controller.hpp"
#include "../Entity/Enemy.hpp"
#include "../Logic/Scorer.hpp"
//#include "../Logic/EnemyGroup.hpp"
#include "../Logic/Commander.hpp"

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
        auto startLine = Sprite::create("img/start_line.png");
        startLine->setPosition(X  , pos.y);
        addChild(startLine , 50);
        
        auto car = Car::create("img/car.png", 700, pos, Direction::CCW);
        car->setBlastRes("img/zha.png");
        addChild(car , 100);
        
        Controller::getInstance()->getScorer()->setUserCar(car);
        
        for (int i = 0 ; i < 3; i++) {
            int l = 95;
            auto enemy = Enemy::create("img/car2.png", 700, Vec2(POS_R.x - 70 - l * i, POS_R.y + R_OUTER), Direction::CW);
            enemy->setTag(i);
            enemy->setBlastRes("img/zha2.png");
            enemy->setCommander(Controller::getInstance()->getCommander());
            Controller::getInstance()->getScorer()->addEnemy(enemy);
            addChild(enemy);
        }
        
        return true;
    }
    return false;
}







