//
//  NormalLayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/30.
//
//

#include "NormalLayer.hpp"
#include "../Logic/Controller.hpp"
#include "../utils/Signal.hpp"
#include "../constant.h"

USING_NS_CC;

NormalLayer::NormalLayer():
_btnPause(nullptr),
_btnStart(nullptr),
_lblScore(nullptr){
    
}

NormalLayer::~NormalLayer(){
    
}

bool NormalLayer::init(){
    if (Layer::init()) {
        createCallback();
        createWidget();
        bindEvent();
        setVisible(false);
        return true;
    }
    return false;
}

void NormalLayer::createCallback(){
    
    _callBack[CB::pause] = [](Ref *){
        if (Director::getInstance()->isPaused()) {
            Director::getInstance()->resume();
        }else{
            Director::getInstance()->pause();
        }
    };
    
    _callBack[CB::start] = [this](Ref *){
        _btnStart->setVisible(false);
        _lblScore->setVisible(true);
        Controller::getInstance()->start();
    };
    
}

void NormalLayer::createWidget(){
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    
    _lblScore = Label::createWithTTF("0" , "fonts/Marker Felt.ttf" , 150);
    _lblScore->setPosition(centerPos);
    addChild(_lblScore);
    _lblScore->setVisible(false);
    
    _btnPause = ui::Button::create("CloseNormal.png");
    _btnPause->setPosition(Vec2(winSize.width * 0.92 , winSize.height * 0.92));
    _btnPause->setScale(2.5);
    addChild(_btnPause);
    
    _btnStart = ui::Button::create("img/play.png");
    _btnStart->setPosition(centerPos);
    addChild(_btnStart);
    
}

void NormalLayer::bindEvent(){
    
    _btnPause->addClickEventListener(_callBack[CB::pause]);
    
    _btnStart->addClickEventListener(_callBack[CB::start]);
    
    Controller::getInstance()->getSignal()->registerEvent(ON_SCORE_CHANGE, this, TO_SIG_SEL(NormalLayer::refreshScore), 0);
}

void NormalLayer::playRewardEff(){
    if (isVisible()) {
        GET_CENTER_WINSIZE;
        auto good = Label::createWithTTF("Good" , "fonts/Marker Felt.ttf" , 80);
        addChild(good , 100);
        good->setPosition(centerPos);
        auto moveBy = MoveBy::create(0.6 , Vec2(0 , 200));
        auto fadeOut = FadeOut::create(0.6);
        auto spawn = Spawn::create(moveBy , fadeOut , nullptr);
        auto easeIn = EaseIn::create(spawn , 0.5);
        auto callFunc = CallFuncN::create([](Node * node){
            node->removeFromParent();
        });
        good->runAction(Sequence::create(easeIn , callFunc , NULL));
    }
}

void NormalLayer::pop(){
    setVisible(true);
}

void NormalLayer::pickUp(){
    setVisible(false);
}

bool NormalLayer::refreshScore(va_list args){
    
    int score = va_arg(args,int);
    
    char str[10];
    
    sprintf(str, "%d" , score);
    
    _lblScore->setString(str);
    
    return true;
}




