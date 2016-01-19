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
    
    CC_SYNTHESIZE_READONLY(int , _GameState , GameState);
    
    void start();
    
    void stop();
    
    void pause();
    
protected:
    Controller();
    
    static Controller * s_pController;
    
};

#endif /* Controller_hpp */
