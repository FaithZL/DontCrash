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
    
    void setExtraScoreByTag(int enemyTag);
    
    float getExtraScoreByTag(int enemyTag);
    
    void setDistance(int enemyTag , float distance);
    
    float getPreDistance(int enemyTag);
    
    void setFarthestFlagbyTag(int enemyTag , bool flag);
    
    bool getFarthestFlagbyTag(int enemyTag);
    
    static Car * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void update(float d);
    
    virtual void changeTrack();
    
protected:
    
    float _extraScore[3];
    
    float _preDis[3];
    //present whether arrive at farthest distance by enemy tag
    bool _bFarthestFlag[3];
};

#endif /* Car_hpp */
