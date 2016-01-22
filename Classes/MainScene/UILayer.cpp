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
#include "constant.h"
USING_NS_CC;

UILayer::UILayer():
_over(nullptr),
_normal(nullptr),
_preState(-1)
{
}

UILayer::~UILayer()
{
    
}

void UILayer::createCB(){
    
    _callBack[CB::Start] = [](Ref * ref){
        Controller::getInstance()->start();
        (static_cast<ui::Button *>(ref)->setVisible(false));
    };
    
    _callBack[CB::Reset] = [](Ref * ref){
        Controller::getInstance()->reset();
    };
    
    _callBack[CB::Share] = [](Ref * ref){
        CCLOG("share");
    };
    
    _callBack[CB::Fav] = [](Ref * ref){
        CCLOG("favorite");
    };
    
    _callBack[CB::More] = [](Ref * ref){
        CCLOG("more");
    };

    _callBack[CB::Rank] = [](Ref * ref){
        CCLOG("rank");
    };

    _onStateEnter[GameState::GNormal] = [this](){
        _startBtn->setVisible(true);
    };
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    Controller::getInstance()->getUserCar()->changeTrack();
    
    return true;
}

void UILayer::initOverLayer(){
    _over = Layer::create();
    
    auto r = 75;
    
    auto btnReset = ui::Button::create("img/chonglai.png");
    btnReset->addClickEventListener(_callBack[CB::Reset]);
    btnReset->setPosition(POS_R);
    _over->addChild(btnReset);
    
    auto btnShare = ui::Button::create("img/fenxiang.png");
    btnShare->addClickEventListener(_callBack[CB::Share]);
    btnShare->setPosition(Vec2(POS_L.x - r, POS_L.y));
    _over->addChild(btnShare);
    
    auto btnFav = ui::Button::create("img/fav.png");
    btnFav->addClickEventListener(_callBack[CB::Fav]);
    btnFav->setPosition(Vec2(POS_L.x , POS_L.y - r));
    _over->addChild(btnFav);
    
    auto btnRank = ui::Button::create("img/paihang.png");
    btnRank->addClickEventListener(_callBack[CB::Rank]);
    btnRank->setPosition(Vec2(POS_L.x + r, POS_L.y));
    _over->addChild(btnRank);
    
    auto btnMore = ui::Button::create("img/gengduo1.png");
    btnMore->addClickEventListener(_callBack[CB::More]);
    btnMore->setPosition(Vec2(POS_L.x , POS_L.y + r));
    _over->addChild(btnMore);
    
    _over->setVisible(false);
    
    addChild(_over);
    
    _layers[GameState::GOver] = _over;
}


void UILayer::initRunningLayer(){
    _normal = Layer::create();
    auto startBtn = ui::Button::create("img/play.png");
    auto winSize = Director::getInstance()->getWinSize();
    startBtn->setPosition(Vec2(winSize.width / 2 , winSize.height / 2));
    startBtn->addClickEventListener(_callBack[CB::Start]);
    _normal->addChild(startBtn);
    _normal->setVisible(false);
    addChild(_normal);
    _startBtn = startBtn;
    _layers[GameState::GNormal] = _normal;
}

void UILayer::setCurLayer(int newState){
    if (_preState != -1) {
        _layers[_preState]->setVisible(false);
        if (_onStateExit[_preState]) {
            _onStateExit[_preState]();
        }
    }
    _layers[newState]->setVisible(true);
    if (_onStateEnter[newState]) {
        _onStateEnter[newState]();
    }
    _preState = newState;
}


bool UILayer::init(){
    if (Layer::init()) {
        createCB();
        initOverLayer();
        initRunningLayer();
        
        setCurLayer(GameState::GNormal);
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


