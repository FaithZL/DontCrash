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
    
    static Car * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void update(float d);
    
    virtual void changeTrack();
    
};

#endif /* Car_hpp */
