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
#include "FSM.h"

class FSM;

enum CarState
{
    Circle,
    Line
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
    
    CC_SYNTHESIZE_READONLY(cocos2d::Vec2 , _prePos, PrePos);
    
    CC_SYNTHESIZE(float , _curRadius , CurRadius);
    
    CC_SYNTHESIZE(std::string , _blastRes , BlastRes);
    
    CC_SYNTHESIZE_READONLY(cocos2d::Vec2 , _originPos, OriginPos);
    
    inline void setVelo(float newVelo , bool isAlways){
        if (isAlways) {
            _normalVelo = newVelo;
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
    
    virtual void changeTrack();
    
    inline bool isChangeToCircle(){
        if (getCurrentStateName() == CarState::Circle && getPreviousStateName() == CarState::Line) {
            return true;
        }
        return false;
    }
    
    inline bool isChangeToLine(){
        if (getPreviousStateName() == CarState::Line && getPreviousStateName() == CarState::Circle) {
            return true;
        }
        return false;
    }
    
protected:
    
    float _normalVelo;
    
    float _originVelo;
    
    float _originAngle;
    
    std::string _normalRes;
};

#endif /* BaseCar_hpp */
