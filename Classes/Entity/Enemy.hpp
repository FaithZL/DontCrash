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



enum AttempToChange{
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

class EnemyGroup;

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    CC_SYNTHESIZE_READONLY(int , _attempToChange , AttempToChange);
    
    CC_SYNTHESIZE(EnemyGroup *, _group, Group);
    
    inline void setAttempToChange(int var){
        if (var == AttempToChange::Disable || var == AttempToChange::CanSet) {
            _attempToChange = var;
            return;
        }
        if (_attempToChange == AttempToChange::CanSet) {
            _attempToChange = var;
        }
    }
    
    inline void speedUp(){
        _curVelo = _normalVelo * 1.25;
        _angVelo = _curVelo / R_OUTER;
    }
    
    inline void speedDown(){
        _curVelo = _normalVelo * 0.75;
        _angVelo = _curVelo / R_OUTER;
    }
    
    inline void speedResume(){
        _curVelo = _normalVelo;
        _angVelo = _normalVelo / R_OUTER;
    }
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void enterCircleCallBack();
    
    virtual void updateRadius(float d);
    
    virtual void changeTrack();
    
    virtual void reset();
    
    virtual void update(float d);
    
    virtual void enterLineCallBack();
    
//    virtual void circleUpdate(float d);
    
};


#endif /* Enemy_hpp */
