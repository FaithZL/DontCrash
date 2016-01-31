//
//  EnterScene.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#include "EnterScene.hpp"
#include "../constant.h"

USING_NS_CC;

EnterScene::EnterScene():
_imitatedBy(nullptr),
_L(nullptr),
_ThanksTo(nullptr),
_umoni(nullptr),
_Z(nullptr){
    
}

EnterScene::~EnterScene(){
    
}

bool EnterScene::init(){
    if (Scene::init()) {
        start();
        return true;
    }
    return false;
}

void EnterScene::start(){
    
}












