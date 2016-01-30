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

USING_NS_CC;

OverLayer::OverLayer():
_btnFav(nullptr),
_btnMore(nullptr),
_btnRank(nullptr),
_btnReset(nullptr),
_btnShare(nullptr){
    
}

OverLayer::~OverLayer(){
    
}

void OverLayer::createCallback(){
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
}