//
//  Scoring.hpp
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
    
    CC_SYNTHESIZE_READONLY(int , _score, Score);
    
    CREATE_FUNC(Scorer);
    
    virtual void update(float d);
    
    virtual bool init();
    
    void setCars(Car * car , cocos2d::Vector<Enemy *> * enemies);
    
protected:
    
    Car * _car;
    
    int _enemyState;
    
    cocos2d::Vector<Enemy *> * _enemies;
};

#endif /* Scorer_hpp */
