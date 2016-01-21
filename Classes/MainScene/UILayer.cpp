//
//  UILayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "UILayer.hpp"
#include "Controller.hpp"
#include "Car.hpp"
#include "Enemy.hpp"
USING_NS_CC;

UILayer::UILayer():
_startBtn(nullptr)
{
    
}

UILayer::~UILayer()
{
    
}

void UILayer::onStartClick(cocos2d::Ref * ref)
{
    Controller::getInstance()->start();
    _startBtn->setVisible(false);
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    CCLOG("ontouch");
    
    Controller::getInstance()->getUserCar()->changeTrack();
    
    auto es = Controller::getInstance()->getEnemies();
    
    for(auto &it : *es)
    {
        it->changeTrack();
    }
    
    return true;
}

bool UILayer::init()
{
    if (Layer::init()) {
        
        _startBtn = ui::Button::create();
        
        _startBtn->loadTextureNormal("img/play.png");
        
        auto winSize = Director::getInstance()->getWinSize();
        _startBtn->cocos2d::Node::setPosition(winSize.width / 2 , winSize.height / 2);
        
        _startBtn->addClickEventListener(CC_CALLBACK_1(UILayer::onStartClick, this));
        
        addChild(_startBtn);
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


