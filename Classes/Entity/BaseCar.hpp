//
//  BaseCar.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef BaseCar_hpp
#define BaseCar_hpp

#include "cocos2d.h"
#include "../utils/FSM/FSM.h"
#include "../constant.h"

class FSM;

enum CarState
{
    Circle,
    Line
};

enum TrackState{
    ToOuter,
    ToInner,
    Normal
    //    Disabled
};

enum Direction{
    CW,
    CCW
};

enum UDLR{
    up,
    down,
    left,
    right
};

class BaseCar : public cocos2d::Sprite , public FSM
{
    
public:
    BaseCar();
    ~BaseCar();
    
    CC_SYNTHESIZE_READONLY(int , _trackState , TrackState);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Vec2 , _prePos, PrePos);
    
    CC_SYNTHESIZE(float , _curRadius , CurRadius);
    
    CC_SYNTHESIZE(std::string , _blastRes , BlastRes);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Vec2 , _originPos, OriginPos);
    
    inline void setVelo(float newVelo , bool isAlways){
        if (isAlways) {
            _normalVelo = newVelo;
            _angVelo = _normalVelo / R_OUTER;
        }
        _curVelo = newVelo;
    }
    
    virtual int getUDLR();
    
    CC_SYNTHESIZE_READONLY(float , _curVelo , Velo);
    
    CC_SYNTHESIZE(int , _direction , Direction);
    
    virtual void initFSM();
    
    virtual bool init(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
        
    virtual void reset();
    
    virtual void lineUpdate(float d);
    
    virtual void enterLineCallBack();
    
    virtual void circleUpdate(float d);
    
    virtual void enterCircleCallBack();
    
    virtual void update(float delta);
    
    virtual void blast();
    
    inline void resetFSM(){
        _currentState = nullptr;
        _previousState = nullptr;
        _delayedStateName = CarState::Line;
    }
    
    inline bool isChangeToCircle(){
        if (_prePos.x <= POS_R.x && getPositionX() > POS_R.x) {
            return true;
        }
        if (_prePos.x >= POS_L.x && getPositionX() < POS_L.x) {
            return true;
        }
        return false;
    }
    
    inline bool isChangeToLine(){
        if (_prePos.x < POS_L.x && getPositionX() >= POS_L.x) {
            return true;
        }
        if (_prePos.x > POS_R.x && getPositionX() <= POS_R.x) {
            return true;
        }
        return false;
    }
    
protected:
    
    float _normalVelo;
    //base of PI
    float _angVelo;
    
    float _originVelo;
    
    float _originAngle;
    
    std::string _normalRes;
};

#endif /* BaseCar_hpp */
