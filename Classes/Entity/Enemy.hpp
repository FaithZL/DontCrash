//
//  Enemy.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "cocos2d.h"
#include "BaseCar.hpp"
#include "SimpleAudioEngine.h"

class EnemyGroup;
class Commander;

class Enemy : public BaseCar
{
public:
    Enemy();
    ~Enemy();
    
    CC_SYNTHESIZE(EnemyGroup * , _group, Group);
    
    CC_SYNTHESIZE(Commander * , _commander, Commander);

    CC_SYNTHESIZE(bool , _bChangeTrack , isChangeTrack);
    
    inline void speedUp(){
        if (_curVelo == _normalVelo * 1.25) {
            return;
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cars_gather.mp3");
        _curVelo = _normalVelo * 1.25;
        _angVelo = _curVelo / R_OUTER;
    }
    
    inline void speedDown(){
        if (_curVelo == _normalVelo * 0.75) {
            return;
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cars_separate.mp3");
        _curVelo = _normalVelo * 0.75;
        _angVelo = _curVelo / R_OUTER;
    }
    
    inline void speedResume(){
        _curVelo = _normalVelo;
        _angVelo = _normalVelo / R_OUTER;
    }
    
    Enemy * getPre();
    
    void followHead();
    
    Enemy * getNext();
    
    static Enemy * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void enterCircleCallBack();
    
    virtual void randChangeTrack();
    
    virtual void updateRadius(float d);
    
    virtual void startChangeTrack();
    
    virtual void reset();
    
    virtual void update(float d);
    
    inline bool isChangeTrack(){
        return _bChangeTrack;
    }
};


#endif /* Enemy_hpp */
