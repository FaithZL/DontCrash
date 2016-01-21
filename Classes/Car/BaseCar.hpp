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

class BaseCar : public cocos2d::Sprite , public FSM
{
    
public:
    BaseCar();
    ~BaseCar();
    
    CC_SYNTHESIZE(float , _curRadius , CurRadius);
    
    CC_SYNTHESIZE(std::string , _blastRes , BlastRes);
    
    CC_SYNTHESIZE(float , _curVelo , Velo);
    
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
    
protected:
    cocos2d::Vec2 _originPos;
    
    float _originVelo;
    
};

#endif /* BaseCar_hpp */
