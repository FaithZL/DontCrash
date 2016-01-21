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
class UILayer : public cocos2d::Layer
{
public:
    UILayer();
    ~UILayer();
    CREATE_FUNC(UILayer);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    void onStartClick(Ref * ref);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _running , RunningLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _pause , PauseLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _ready , readyLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Layer * , _over , RunniLayer);
    
    void initReadyLayer();
    
    void initRunningLayer();
    
    void initPauseLayer();
    
    void initOverLayer();
    
    void setCurLayer(int state);

    virtual bool init();
    
protected:
    
    cocos2d::Layer * _layers[4];
    
    int _preState;
};

#endif /* UILayer_hpp */
