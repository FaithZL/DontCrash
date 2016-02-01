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
#include "FSM.h"

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
    GReady,
    GPause,
    GRunning,
    GOver,
    length
};

class Controller : public cocos2d::Ref , public FSM
{
public:
    ~Controller();
    
    static Controller * getInstance();
    
    static void destroyInstance();
    
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY(int , _gameState , CurGameState);
    
    bool initFSM();
    
    CC_SYNTHESIZE_READONLY(UserData * , _userData , UserData);
    
    CC_SYNTHESIZE_READONLY(MainUI * , _mainUI , MainUI);
    
    CC_SYNTHESIZE(bool , _bAuto , Auto);
    
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
    
    void ready();
    
    void pause();
    
    void stop();
    
    void resume();
    
    void reset();
    
protected:
    
    Controller();
    
    static Controller * s_pController;
    
    GameLayer * _gameLayer;
    
    cocos2d::Scheduler * _scheduler;
    
};

#endif /* Controller_hpp */
