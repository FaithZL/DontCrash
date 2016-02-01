//
//  OverLayer.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/30.
//
//

#include "OverLayer.hpp"
#include "constant.h"
#include "../Logic/Controller.hpp"
#include "../Data/UserData.hpp"
#include "../Logic/Scorer.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

OverLayer::OverLayer():
_btnFav(nullptr),
_btnMore(nullptr),
_btnRank(nullptr),
_btnReset(nullptr),
_btnShare(nullptr),
_lblScore(nullptr),
_lblBestScore(nullptr){
    
}

OverLayer::~OverLayer(){
    
}

void OverLayer::createCallback(){
    _callBack[CB::Reset] = [](Ref * ref){
        Controller::getInstance()->reset();
        Controller::getInstance()->start();
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

}

bool OverLayer::init(){
    if (Layer::init()) {
        createCallback();
        createWidget();
        bindEvent();
        setVisible(false);
        return true;
    }
    return false;
}

void OverLayer::createWidget(){
    
    auto r = 75;
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPos = Vec2(winSize.width / 2 , winSize.height / 2);
    
    _lblScore = Label::createWithTTF("0" , "fonts/Marker Felt.ttf" , 150);
    _lblScore->setPosition(centerPos);
    addChild(_lblScore);
    
    _lblBestScore = Label::createWithTTF("best : 0" , "fonts/Marker Felt.ttf" , 60);
    _lblBestScore->setPosition(centerPos.x , centerPos.y - 100);
    addChild(_lblBestScore);
    
    _btnReset = ui::Button::create("img/chonglai.png");
    _btnReset->setPosition(POS_R);
    addChild(_btnReset);
    
    _btnShare = ui::Button::create("img/fenxiang.png");
    _btnShare->setPosition(Vec2(POS_L.x - r, POS_L.y));
    addChild(_btnShare);
    
    _btnFav = ui::Button::create("img/fav.png");
    _btnFav->setPosition(Vec2(POS_L.x , POS_L.y - r));
    addChild(_btnFav);
    
    _btnRank = ui::Button::create("img/paihang.png");
    _btnRank->setPosition(Vec2(POS_L.x + r, POS_L.y));
    addChild(_btnRank);
    
    _btnMore = ui::Button::create("img/gengduo1.png");
    _btnMore->setPosition(Vec2(POS_L.x , POS_L.y + r));
    addChild(_btnMore);
    
    
}

void OverLayer::setLabel(){
    
    int score = Controller::getInstance()->getScorer()->getScore();
    char str[16];

    sprintf(str , "%d" , score);
    
    _lblScore->setString(str);
    
    int bestScore = Controller::getInstance()->getUserData()->getBestScore();
    
    if (score > bestScore) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/NewHigh.mp3");
        Controller::getInstance()->getUserData()->setBestScore(score);
        sprintf(str , "best %d" , score);
    }else{
        sprintf(str , "best   %d" , bestScore);
    }
    
    _lblBestScore->setString(str);
    
}

void OverLayer::bindEvent(){
    _btnReset->addClickEventListener(_callBack[CB::Reset]);
    _btnShare->addClickEventListener(_callBack[CB::Share]);
    _btnFav->addClickEventListener(_callBack[CB::Fav]);
    _btnRank->addClickEventListener(_callBack[CB::Rank]);
    _btnMore->addClickEventListener(_callBack[CB::More]);
}

void OverLayer::pickUp(){
    setVisible(false);
}

void OverLayer::pop(){
    setVisible(true);
    setLabel();
}






