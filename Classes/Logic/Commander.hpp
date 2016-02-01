//
//  Commander.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/29.
//
//

#ifndef Commander_hpp
#define Commander_hpp

#include "cocos2d.h"
#include "../utils/FSM/FSM.h"
#include "Scorer.hpp"

class Enemy;

enum GroupState {
    g3,
    g12,
    g111
};

class Commander : public FSM , public cocos2d::Ref{

public:
    ~Commander();
    Commander();
    
    CREATE_FUNC(Commander);
    
    virtual bool init();
    
    virtual void initFSM();
    
    void g3enter();
    
    void g3update(float d);
    
    void g12enter();
    
    void g12update(float d);
    
    void g111enter();
    
    void g111update(float d);
    
    bool isAllTheSame(int from , int to , std::string fieldName...);
    
    virtual void update(float d);
    
    virtual void reset();
    
    inline void resetFSM(){
        _delayedStateName = GroupState::g3;
        _currentState = nullptr;
        _previousState = nullptr;
    }
    
    inline void setScorer(Scorer * scorer){
        _scorer = scorer;
        _enemies = _scorer->getEnemies();
    }
    
    inline cocos2d::Vector<Enemy *> * getEnemies(){
        return _enemies;
    }
    
    inline bool isRandSwitchOn(){
        return _randSwitch;
    }
    
    void formation();
    
protected:
    
    float _timer;
    
    bool _bFormated;
    
    bool _randSwitch;
    
    Scorer * _scorer;
    
    cocos2d::Vector<Enemy *> * _enemies;
    
};

#endif /* Commander_hpp */
