//
//  Car.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/19.
//
//

#ifndef Car_hpp
#define Car_hpp

#include "BaseCar.hpp"

class Car : public BaseCar
{
public:
    Car();
    
    ~Car();
    
    void setExtraScoreByTag(int tag);
    
    int getExtraScoreByTag(int tag);
    
    static Car * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void update(float d);
    
    virtual void changeTrack();
    
protected:
    int _extraScore[3];
};

#endif /* Car_hpp */
