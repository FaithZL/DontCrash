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

class Enemy;
class Scorer;

class Group : public cocos2d::Ref , public FSM{
public:
    Group();
    ~Group();
    
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
    
    inline void setScorer(Scorer * scorer){
        _scorer = scorer;
    }
    
    virtual void update(float d);
    
    virtual void reset();
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
protected:
    
    bool _bCanSwitch;
    
    Scorer * _scorer;
    
    cocos2d::Vector<Enemy *> _enemies;
};



#endif /* Group_hpp */
