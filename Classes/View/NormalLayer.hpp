//
//  NormalLayer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/30.
//
//

#ifndef NormalLayer_hpp
#define NormalLayer_hpp

#include "cocos2d.h"

class NormalLayer : public cocos2d::Layer {
    
public:
    
    NormalLayer();
    ~NormalLayer();
    
    enum CB{
        pause,
        start,
        length
    };
    
    virtual bool init();
    
    CREATE_FUNC(NormalLayer);
    
    void createCallback();
    
    void createButtons();
    
    void bindEvent();
    
    void pop();
    
    void pickUp();
    
};

#endif /* NormalLayer_hpp */
