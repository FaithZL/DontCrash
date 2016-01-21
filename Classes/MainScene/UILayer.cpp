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
_over(nullptr),
_ready(nullptr),
_running(nullptr),
_pause(nullptr),
_preState(-1)
{
    
}

UILayer::~UILayer()
{
    
}

void UILayer::onStartClick(cocos2d::Ref * ref)
{
    Controller::getInstance()->start();
    
    (static_cast<Node *>(ref))->setVisible(false);
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    Controller::getInstance()->getUserCar()->changeTrack();
    
    return true;
}

void UILayer::initOverLayer(){
    _over = Layer::create();
    
}

void UILayer::initPauseLayer(){
    
}

void UILayer::initRunningLayer(){
    
}

void UILayer::setCurLayer(int state){
    if (_preState != -1) {
        _layers[_preState]->setVisible(false);
    }
    _layers[state]->setVisible(true);
    _preState = state;
}

void UILayer::initReadyLayer(){
    
    auto startBtn = ui::Button::create();
    startBtn->loadTextureNormal("img/play.png");
    _ready = Layer::create();
    addChild(_ready);
    auto winSize = Director::getInstance()->getWinSize();
    startBtn->cocos2d::Node::setPosition(winSize.width / 2 , winSize.height / 2);
    startBtn->addClickEventListener(CC_CALLBACK_1(UILayer::onStartClick, this));
    _ready->addChild(startBtn);
}

bool UILayer::init(){
    if (Layer::init()) {
        
        initOverLayer();
        initPauseLayer();
        initReadyLayer();
        initRunningLayer();
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


