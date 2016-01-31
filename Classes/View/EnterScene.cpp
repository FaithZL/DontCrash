//
//  EnterScene.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#include "EnterScene.hpp"
#include "../constant.h"
#include "SimpleAudioEngine.h"
#include "../Logic/Controller.hpp"


USING_NS_CC;

EnterScene::EnterScene():
_imitatedBy(nullptr),
_LL(nullptr),
_ThanksTo(nullptr),
_umoni(nullptr),
_Z(nullptr),
_bCanTouch(false){
    
}

EnterScene::~EnterScene(){
    
}

void EnterScene::preLoad(){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/cars_separate.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/crash.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/NewHigh.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/perfect.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/point01.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/point02.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/point03.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/tap_2.mp3");
}

bool EnterScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    if (_bCanTouch) {
        Director::getInstance()->replaceScene(Controller::getInstance()->createScene());
    }
    
    return true;
    
}

bool EnterScene::init(){
    if (Scene::init()) {
        preLoad();
        scheduleOnce([this](float d){
            this->start();
        }, 0.5, "6");
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(EnterScene::onTouchBegan,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        return true;
    }
    return false;
}

void EnterScene::start(){
    GET_CENTER_WINSIZE;
    _ThanksTo = Label::createWithTTF("Thanks to", "fonts/Marker Felt.ttf" , 120);
    _ThanksTo->setPosition(centerPos.x - 240, centerPos.y + 130);
    addChild(_ThanksTo);
    _ThanksTo->setColor(Color3B(32, 223, 137));
    _ThanksTo->setOpacity(0);
    _ThanksTo->runAction(FadeIn::create(1));
    
    
    _spumoni = Sprite::create("img/logo2.png");
    _spumoni->setPosition(centerPos.x + 230 , centerPos.y + 130);
    _spumoni->setScale(0.1);
    auto spawn = Spawn::create(RotateBy::create(1 , 360 * 3), ScaleTo::create(1, 1.1), nullptr);
    _spumoni->runAction(spawn);
    addChild(_spumoni);
    
    _imitatedBy = Label::createWithTTF("Imitated   by", "fonts/Marker Felt.ttf" , 120);
    _imitatedBy->setPosition(centerPos.x - 220 , centerPos.y - 130);
    _imitatedBy->setColor(Color3B(223, 201, 32));
    _imitatedBy->setOpacity(0);
    _imitatedBy->runAction(FadeIn::create(1));
    addChild(_imitatedBy);
    
    _Z = Label::createWithTTF("Z", "fonts/Marker Felt.ttf" , 120);
    _Z->setPosition(centerPos.x + 800 , centerPos.y - 130);
    _Z->setColor(Color3B(32, 188, 223));
    addChild(_Z);
    
    _LL = Label::createWithTTF("L", "fonts/Marker Felt.ttf" , 120);
    _LL->setPosition(centerPos.x + 870 , centerPos.y - 130);
    _LL->setColor(Color3B(32, 188, 223));
    addChild(_LL);
    
    scheduleOnce([this](float d){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cars_separate.mp3");
        auto ease = EaseIn::create(MoveBy::create(0.7, Vec2(- 600, 0)), 0.2);
        _Z->runAction(ease);
    }, 1, "1");
    
    scheduleOnce([this](float d){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cars_gather.mp3");
        auto ease = EaseIn::create(MoveBy::create(0.7, Vec2(- 600, 0)), 0.2);
        _LL->runAction(ease);
    }, 1.5f, "2");
    
    scheduleOnce([this , centerPos](float d){
        _bCanTouch = true;
        
        auto text = Label::createWithTTF("touch for continue", "fonts/Marker Felt.ttf" , 40);
        text->setPosition(centerPos);
        auto rep = RepeatForever::create(Sequence::create(FadeOut::create(0.7), FadeIn::create(0.7),nullptr));
        text->runAction(rep);
        
        this->addChild(text);
        
    }, 2.5f , "3");
    
}












