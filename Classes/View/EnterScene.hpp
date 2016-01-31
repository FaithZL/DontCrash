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
    
    void start();
    
protected:
    
    cocos2d::Label * _Z;
    
    cocos2d::Label * _L;
    
    cocos2d::Label * _ThanksTo;
    
    cocos2d::Label * _umoni;
    
    cocos2d::Label * _imitatedBy;
};

#endif /* EnterScene_hpp */
