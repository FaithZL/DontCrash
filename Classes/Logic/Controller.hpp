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
#include "Car.hpp"

class Car;
class Enemy;
class UILayer;
class GameLayer;
class Scorer;

enum GameState
{
    GNormal,
    GOver,
    length
};

class Controller : public cocos2d::Ref
{
public:
    ~Controller();
    
    static Controller * getInstance();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(int , _GameState , CurGameState);
    
    CC_SYNTHESIZE(Car * , _car , UserCar);
    
    cocos2d::Scene * createScene();
    
    void addEnemy(Enemy * enemy);
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
    void start();
    
    void update(float d);
    //Collision Detection , scoring ...
    void doPerFrame(float d);
    
    bool isCollision(cocos2d::Sprite * node1 , cocos2d::Sprite * node2);
    
    void scheduleUpdate();
    
    void unscheduleUpdate();
    
    void pause();
    
    void over();
    
    void reset();
    
    void initScorer();
    
protected:
    Controller();
    
    static Controller * s_pController;
    
    cocos2d::Vector<Enemy *> _enemies;
    
    UILayer * _uiLayer;
    
    GameLayer * _gameLayer;
    
    cocos2d::Scheduler * _scheduler;
    
    Scorer * _scorer;
    
};

#endif /* Controller_hpp */
