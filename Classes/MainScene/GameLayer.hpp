//
//  GameLayer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
    GameLayer();
    
    ~GameLayer();
    
    CREATE_FUNC(GameLayer);
    
    virtual bool init();
private:
    cocos2d::Sprite * _bg;
    
    cocos2d::Sprite * _bg2;
    
//    cocos2d::Sprite * _car;
    
    cocos2d::Sprite * _track;
};

#endif /* GameLayer_hpp */
