//
//  Controller.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef Controller_hpp
#define Controller_hpp

#include "cocos2d.h"

class Car;
class Enemy;

enum GameState
{
    Pause,
    Run,
    Stop
};

class Controller : public cocos2d::Ref
{
public:
    ~Controller();
    
    static Controller * getInstance();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(int , _GameState , CurGameState);
    
    CC_SYNTHESIZE(Car * , _car , UserCar);
    
    void addEnemy(Enemy * enemy);
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
    void start();
    
    void pause();
    
    void reset();
    
protected:
    Controller();
    
    static Controller * s_pController;
    
    cocos2d::Vector<Enemy *> _enemies;
    
};

#endif /* Controller_hpp */
