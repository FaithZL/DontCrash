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
    
    virtual bool init();
protected:
    
    ui::Button * _startBtn;
};

#endif /* UILayer_hpp */
