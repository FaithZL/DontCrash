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
#include "../utils/FSM/FSM.h"
USING_NS_CC;

class Controller;

class MainUI : public cocos2d::Layer , public FSM
{
public:
    
    enum CB{
        Start,
        Pause,
        Share,
        More,
        Rank,
        Fav,
        Reset,
        length
    };
    
    MainUI();
    ~MainUI();
    CREATE_FUNC(MainUI);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _normal , NormalLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _over , OverLayer);
    
    void initFSM();
    
    void initNormalLayer();
    
    void initOverLayer();
    
    void initScore();
    
    void createCB();

    virtual bool init();
    
    void overLayerPop();
    
    void reset();
    
    bool refreshScore(va_list args);
    
protected:
    
    cocos2d::Layer * _layers[3];
    
    ui::Button * _startBtn;
    
    cocos2d::Label * _score;
    
    std::function<void(Ref *)> _callBack[CB::length];
    
    std::function<void()> _onStateEnter[2];
    
    std::function<void()> _onStateExit[2];
    
    int _preState;
};

#endif /* MainUI_hpp */
