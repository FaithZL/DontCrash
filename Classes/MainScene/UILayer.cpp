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
USING_NS_CC;

UILayer::UILayer()
{
    
}

UILayer::~UILayer()
{
    
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    CCLOG("ontouch");
    
    Controller::getInstance()->getUserCar()->changeTrack();
    
    return true;
}

bool UILayer::init()
{
    if (Layer::init()) {
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}