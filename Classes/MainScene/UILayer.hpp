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

USING_NS_CC;
class UILayer : public cocos2d::Layer
{
public:
    UILayer();
    ~UILayer();
    CREATE_FUNC(UILayer);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    virtual bool init();
    
};

#endif /* UILayer_hpp */
