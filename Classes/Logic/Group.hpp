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

class Group : public cocos2d::Ref , public FSM{
public:
    Group();
    ~Group();
    
    virtual bool init();
    
    CC_SYNTHESIZE(int , _enemyState, EnemyState);
    
    CREATE_FUNC(Group);
    
    void initFSM();
    
    void addEnemy(Enemy * enemy);
    
    void controlEnemyState(float d , int score);
    
    void randonChangeTrack(float d);
    
    virtual void update(float d);
    
    virtual void reset();
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
protected:
    
    bool _bCanSwitch;
    
    cocos2d::Vector<Enemy *> _enemies;
};



#endif /* Group_hpp */
