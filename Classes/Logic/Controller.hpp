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
class MainUI;
class GameLayer;
class Scorer;
class Signal;
class Commander;
class UserData;

enum GameState
{
    GNormal,
    GRunning,
    GOver,
    length
};

class Controller : public cocos2d::Ref
{
public:
    ~Controller();
    
    static Controller * getInstance();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(int , _gameState , CurGameState);
    
    CC_SYNTHESIZE_READONLY(UserData * , _userDate , UserData);
    
    CC_SYNTHESIZE_READONLY(Commander * , _commander , Commander);
    
    CC_SYNTHESIZE_READONLY(Signal * , _signal, Signal);
    
    CC_SYNTHESIZE_READONLY(Scorer * , _scorer, Scorer);
    
    cocos2d::Scene * createScene();
    
    cocos2d::Vector<Enemy *> * getEnemies();
    
    void start();
    
    void update(float d);
    
    void scheduleUpdate();
    
    void scheduleOnce(std::function<void(float)> &callback, float delay , std::string key);
    
    void unscheduleUpdate();
    
    void pause();
    
    void over();
    
    void reset();
    
protected:
    
    Controller();
    
    static Controller * s_pController;
    
    MainUI * _mainUI;
    
    GameLayer * _gameLayer;
    
    cocos2d::Scheduler * _scheduler;
    
};

#endif /* Controller_hpp */
