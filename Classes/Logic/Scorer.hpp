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
    
    CC_SYNTHESIZE(int , _score, Score);
    
    CREATE_FUNC(Scorer);
    
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
    
    void setCars(Car * car , cocos2d::Vector<Enemy *> * enemies);

protected:
    
    Car * _car;
    
    int _enemyState;
    
    cocos2d::Vector<Enemy *> * _enemies;
};

#endif /* Scorer_hpp */
