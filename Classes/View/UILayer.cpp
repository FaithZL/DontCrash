//
//  UILayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#include "UILayer.hpp"
#include "../Logic/Controller.hpp"
#include "../Entity/Car.hpp"
#include "../Entity/Enemy.hpp"
#include "../constant.h"
#include "../utils/FSM/FSMState.h"
#include "../utils/Signal.hpp"
#include "../Logic/Scorer.hpp"
USING_NS_CC;

UILayer::UILayer():
_over(nullptr),
_normal(nullptr),
_score(nullptr),
_preState(-1)
{
}

UILayer::~UILayer()
{
    
}

void UILayer::createCB(){
    
    _callBack[CB::Start] = [this](Ref * ref){
        Controller::getInstance()->start();
        (static_cast<ui::Button *>(ref)->setVisible(false));
        CCLOG("start !");
        _score->setVisible(true);
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
    
    Controller::getInstance()->getSignal()->registerEvent("onScoreChange", this, TO_SIG_SEL(UILayer::refreshScore) , 0);
    
}

bool UILayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event)
{
    if (getCurrentStateName() != GameState::GNormal) {
        return false;
    }
    Controller::getInstance()->getScorer()->getUserCar()->changeTrack();
    
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


void UILayer::initNormalLayer(){
    _normal = Layer::create();
    auto startBtn = ui::Button::create("img/play.png");
    auto winSize = Director::getInstance()->getWinSize();
    
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    
    auto pauseBtn = ui::Button::create("CloseNormal.png");
    pauseBtn->setPosition(Vec2(winSize.width * 0.93, winSize.height * 0.93));
    pauseBtn->setScale(3);
    auto cb = [](Ref * ref){
        if (Director::getInstance()->isPaused()) {
            Director::getInstance()->resume();
            return ;
        }
        Director::getInstance()->pause();
    };
    pauseBtn->addClickEventListener(cb);
    addChild(pauseBtn);
    
    startBtn->setPosition(centerPos);
    startBtn->addClickEventListener(_callBack[CB::Start]);
    _normal->addChild(startBtn);
    _normal->setVisible(false);
    addChild(_normal);
    _startBtn = startBtn;
    _layers[GameState::GNormal] = _normal;
}

void UILayer::initFSM(){
    FSMState normal;
    
    normal.setName(GameState::GNormal);
    normal.enterCallback = [this](){
        _startBtn->setVisible(true);
        _score->setVisible(false);
        _normal->setVisible(true);
    };
    normal.exitCallback = [this](){
        _normal->setVisible(false);
    };
    addState(normal);
    
    FSMState over;
    
    over.setName(GameState::GOver);
    over.enterCallback = [this](){
        _over->setVisible(true);
    };
    over.exitCallback = [this](){
        _over->setVisible(false);
    };
    addState(over);
    
    setNextState(GameState::GNormal);
    FSM::update(0);
}

void UILayer::initScore(){
    _score = Label::createWithTTF("0" , "fonts/Marker Felt.ttf" , 150);
    auto winSize = Director::getInstance()->getWinSize();
    _score->setPosition(Vec2(winSize.width / 2 , winSize.height / 2));
    addChild(_score);
}

void UILayer::reset(){
    translateToState(GameState::GNormal);
}

bool UILayer::refreshScore(va_list args){
   
    int score = va_arg(args,int);
    
    char str[10];
    
    sprintf(str, "%d" , score);
    
    _score->setString(str);
    return true;
}

bool UILayer::init(){
    if (Layer::init()) {
        createCB();
        initOverLayer();
        initNormalLayer();
        
        initScore();
        
        
        
        initFSM();
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}


