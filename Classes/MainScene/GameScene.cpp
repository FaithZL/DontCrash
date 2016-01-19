#include "GameScene.h"

#include "UILayer.hpp"
#include "GameLayer.hpp"

USING_NS_CC;

GameScene::GameScene():
    _gameLayer(nullptr),
    _uiLayer(nullptr)
{
    
}

GameScene::~GameScene()
{
    _uiLayer = nullptr;
    _gameLayer = nullptr;
}

bool GameScene::init()
{
    if (Scene::init()) {
        
        _uiLayer = UILayer::create();
        _gameLayer = GameLayer::create();
        
        addChild(_gameLayer);
        addChild(_uiLayer);
    }
    return false;
}