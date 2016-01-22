//
//  UILayer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef UILayer_hpp
#define UILayer_hpp

#include "cocos2d.h"
#include "UIButton.h"

USING_NS_CC;

class Controller;

class UILayer : public cocos2d::Layer
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
    
    UILayer();
    ~UILayer();
    CREATE_FUNC(UILayer);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _normal , NormalLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _over , OverLayer);
    
    void initRunningLayer();
    
    void initOverLayer();
    
    void setCurLayer(int newState);
    
    void createCB();

    virtual bool init();
    
protected:
    
    cocos2d::Layer * _layers[2];
    
    ui::Button * _startBtn;
    
    std::function<void(Ref *)> _callBack[CB::length];
    
    std::function<void()> _onStateEnter[2];
    
    std::function<void()> _onStateExit[2];
    
    int _preState;
};

#endif /* UILayer_hpp */
