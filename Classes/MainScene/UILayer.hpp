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

class UILayer : public cocos2d::Layer
{
public:
    UILayer();
    ~UILayer();
    CREATE_FUNC(UILayer);
    
    virtual bool init();
    
};

#endif /* UILayer_hpp */
