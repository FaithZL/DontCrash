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

enum ChangeState{
    ToOuter,
    ToInner,
    Normal
};

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void update(float d);
    
    virtual void updateRadius(float d);
    
    virtual void changeTrack();
    
    virtual void circleUpdate(float d);
    
protected:
    int _changeState;
    
};


#endif /* Enemy_hpp */
