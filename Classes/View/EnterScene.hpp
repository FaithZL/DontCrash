//
//  EnterScene.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#ifndef EnterScene_hpp
#define EnterScene_hpp

#include "cocos2d.h"

class EnterScene : public cocos2d::Scene{
    
public:
    EnterScene();
    ~EnterScene();
    
    virtual bool init();
    
    CREATE_FUNC(EnterScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * unused_event);
    
    void start();
    
    void preLoad();
    
protected:
    
    cocos2d::Label * _Z;
    
    cocos2d::Label * _LL;
    
    cocos2d::Label * _ThanksTo;
    
    cocos2d::Label * _umoni;
    
    cocos2d::Sprite * _spumoni;
    
    cocos2d::Label * _imitatedBy;
    
    bool _bCanTouch;
};

#endif /* EnterScene_hpp */
