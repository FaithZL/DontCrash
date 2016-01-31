//
//  MainUI.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef MainUI_hpp
#define MainUI_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
//#include "../utils/FSM/FSM.h"
USING_NS_CC;

class Controller;
class NormalLayer;
class OverLayer;

class MainUI : public cocos2d::Layer
{
public:
    
    MainUI();
    ~MainUI();
    CREATE_FUNC(MainUI);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    CC_SYNTHESIZE_READONLY(NormalLayer * , _normal , NormalLayer);
    
    CC_SYNTHESIZE_READONLY(OverLayer * , _over , OverLayer);
    
    void playRewardEff();

    virtual bool init();
    
    void reset();
    
    void over();
    
    bool refreshScore(va_list args);
    
protected:
    
    
    
};

#endif /* MainUI_hpp */
