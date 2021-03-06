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
    
    Scorer();
    ~Scorer();
    
    CC_SYNTHESIZE_READONLY(int , _score , Score);
    
    CC_SYNTHESIZE(Car * , _car , UserCar);
    
    CC_SYNTHESIZE(int , _circleCount, CircleCount);
    
    CC_SYNTHESIZE(bool , _bHarder, Harder);
    
    CREATE_FUNC(Scorer);
    
    void reset();
    
    void playRewardEff();
    
    bool isCollision();
    
    void scoring(float d);
    
    void update(float d);
    
    void addEnemy(Enemy * enemy);
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
    //if the same track then add a extra score buff
    void checkSameTrack();
    
    void testAuto();
    
    void checkMeet(Car * car , Enemy * enemy);
    
    bool isMeet(Car * car , Enemy * enemy);
    
    virtual bool init();
    
    void recordCircleCount(float d);
    
    void difficultyUp();
    
    void relieve();    

protected:
    
    cocos2d::Vector<Enemy *> _enemies;
};

#endif /* Scorer_hpp */
