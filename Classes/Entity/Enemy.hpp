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

enum AttempTochange{
    False,
    True,
    CanSet
};

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    CC_SYNTHESIZE(int , _trackState , TrackState);
    
    CC_SYNTHESIZE_READONLY(int , _attempToChange , AttempToChange);
    
    inline void setAttempToChange(int var){
        if (_attempToChange == AttempTochange::CanSet) {
            _attempToChange = var;
        }
    }
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void enterCircleCallBack();
    
    virtual void updateRadius(float d);
    
    virtual void changeTrack();
    
    virtual void reset();
    
    virtual void update(float d);
    
    virtual void circleUpdate(float d);
    
};


#endif /* Enemy_hpp */
