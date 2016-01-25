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
class UILayer;
class GameLayer;
class Scorer;
class Signal;

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
    
    CC_SYNTHESIZE_READONLY(Signal * , _signal, Signal);
    
    CC_SYNTHESIZE_READONLY(Scorer * , _scorer, Scorer);
    
    cocos2d::Scene * createScene();
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
    void start();
    
    void update(float d);
    
    void scheduleUpdate();
    
    void unscheduleUpdate();
    
    void pause();
    
    void over();
    
    void reset();
    
protected:
    Controller();
    
    static Controller * s_pController;
    
    UILayer * _uiLayer;
    
    GameLayer * _gameLayer;
    
    cocos2d::Scheduler * _scheduler;
    
};

#endif /* Controller_hpp */
