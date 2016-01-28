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



enum AttempTochange{
    False,
    True,
    CanSet,
    Disable
};

//enum VeloState{
//    vCut = -1,
//    vNormal,
//    vAdd
//};

//enum AttempVeloState{
//    aCut = -1,
//    aNormal,
//    aAdd
//};

class Group;

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    CC_SYNTHESIZE_READONLY(int , _attempToChange , AttempToChange);
    
    CC_SYNTHESIZE(Group *, _group, Group);
    
    inline void setAttempToChange(int var){
        if (var == AttempTochange::Disable || var == AttempTochange::CanSet) {
            _attempToChange = var;
            return;
        }
        if (_attempToChange == AttempTochange::CanSet) {
            _attempToChange = var;
        }
    }
    
    inline void speedUp(){
        _curVelo = _normalVelo * 1.25;
    }
    
    inline void speedDown(){
        _curVelo = _normalVelo * 0.75;
    }
    
    inline void speedResume(){
        _curVelo = _normalVelo;
    }
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void enterCircleCallBack();
    
    virtual void updateRadius(float d);
    
    virtual void changeTrack();
    
    virtual void reset();
    
    virtual void update(float d);
    
//    virtual void circleUpdate(float d);
    
};


#endif /* Enemy_hpp */
