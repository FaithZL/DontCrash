//
//  GameLayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "GameLayer.hpp"
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
        _bg = Sprite::create("HelloWorld.png");
        _bg2 = Sprite::create("img/bg2.png");
        _track = Sprite::create("img/track.png");
        
        
        
        addChild(_bg);
        addChild(_bg2);
        addChild(_track);
        return true;
    }
    return false;
}