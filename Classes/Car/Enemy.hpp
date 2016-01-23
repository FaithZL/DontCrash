//
//  Enemy.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"
#include "BaseCar.hpp"

enum TrackState{
    ToOuter,
    ToInner,
    Normal,
    Disabled
};

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    CC_SYNTHESIZE(int , _trackState , TrackState);
    
    CC_SYNTHESIZE(bool , _bAttempToChange , AttempToChange);
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void enterCircleCallBack();
    
    virtual void updateRadius(float d);
    
    virtual void changeTrack();
    
    virtual void circleUpdate(float d);
    
};


#endif /* Enemy_hpp */
