//
//  Scorer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/22.
//
//

#ifndef Scorer_hpp
#define Scorer_hpp

#include "cocos2d.h"

class Car;
class Enemy;

class Scorer : public cocos2d::Ref {
    
public:
    
    enum EnemyState {
        g3,
        g12,
        g111
    };
    
    Scorer();
    ~Scorer();
    
    CC_SYNTHESIZE_READONLY(int , _score , Score);
    
    CC_SYNTHESIZE(Car * , _car , UserCar);
    
    CREATE_FUNC(Scorer);
    
    void reset();
    
    void playRewardEff();
    
    bool isCollision();
    
    void scoring(float d);
    
    void update(float d);
    
    //if the same track then add a extra score buff
    void checkSameTrack();
    
    void checkMeet(Car * car , Enemy * enemy);
    
    bool isMeet(Car * car , Enemy * enemy);
    
    bool isIntersect(cocos2d::Node * node1 , cocos2d::Node * node2);
    
    virtual bool init();
    
    void addEnemy(Enemy * enemy);
    
    void controlEnemyState(float d);
    
    void randonChangeTrack(float d);

protected:
    
    int _enemyState;
    
    bool _bCanChangeEnemyChange;
    
    cocos2d::Vector<Enemy *>  _enemies;
};

#endif /* Scorer_hpp */
