//
//  Group.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/25.
//
//

#ifndef Group_hpp
#define Group_hpp

#include "cocos2d.h"
#include "FSM.h"

enum GroupState {
    g3,
    g12,
    g111
};

class Enemy;
class Scorer;

class Group : public cocos2d::Ref , public FSM{
public:
    Group();
    ~Group();
    
    enum RandSwitch{
        Off,
        On
    };
    
    virtual bool init();
    
    CREATE_FUNC(Group);
    
    void initFSM();
    
    void g3enter();
    
    void g3update(float d);
    
    void g12enter();
    
    void g12update(float d);
    
    void g111enter();
    
    void g111update(float d);
    
    void addEnemy(Enemy * enemy);
    
    float getDistanceInTrack(Enemy * front , Enemy * back);
    
    inline void setScorer(Scorer * scorer){
        _scorer = scorer;
    }
    
    virtual void update(float d);
    
    virtual void reset();
    
    inline void resetFSM(){
        _delayedStateName = GroupState::g3;
        _currentState = nullptr;
        _previousState = nullptr;
    }

    cocos2d::Vector<Enemy *> * getEnemies();
    
protected:
    
    float _timer;
    
    int _randSwitch;
    
    Scorer * _scorer;
    
    cocos2d::Vector<Enemy *> _enemies;
};



#endif /* Group_hpp */
