//
//  Car.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef Car_hpp
#define Car_hpp

#include "cocos2d.h"
#include "../utils/FSM/FSM.h"

class FSM;

enum TrackId{
    inner,
    outer
};

enum Direction{
    CW,
    CCW
};

class Car : public cocos2d::Sprite , public FSM
{
    
public:
    Car();
    ~Car();
    
    CC_SYNTHESIZE(int , _curTrack , CurTrack);
    
    CC_SYNTHESIZE(std::string , _blastRes , BlastRes);
    
    CC_SYNTHESIZE(float , _velo , Velo);
    
    CC_SYNTHESIZE(int , _direction , Direction);
    
    virtual bool init(float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void start();
    
    virtual void stop();
    
    virtual void pause();
    
    virtual void reset();
    
    virtual void update(float delta);
    
    virtual void blast();
    
    virtual void changeTrack();
    
protected:
    cocos2d::Vec2 _originPos;
    float _originVelo;
};

#endif /* Car_hpp */
