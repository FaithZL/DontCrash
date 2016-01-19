#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class UILayer;
class GameLayer;

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    ~GameScene();
    
    CREATE_FUNC(GameScene);
    
    virtual bool init();
    
private:
    UILayer * _uiLayer;
    GameLayer * _gameLayer;
};

#endif // __HELLOWORLD_SCENE_H__
