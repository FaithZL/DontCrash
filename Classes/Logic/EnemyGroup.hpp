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

class EnemyGroup : public cocos2d::Ref , public FSM{
public:
    EnemyGroup();
    ~EnemyGroup();
    
    enum RandSwitch{
        Off,
        On
    };
    
    virtual bool init();
    
    CREATE_FUNC(EnemyGroup);
    
    void initFSM();
    
    void g3enter();
    
    void g3update(float d);
    
    void g12enter();
    
    void g12update(float d);
    
    void g111enter();
    
    void g111update(float d);
    
    void addEnemy(Enemy * enemy);
    
    bool isAllTheSame(int from , int to , std::string fieldName...);
    
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
