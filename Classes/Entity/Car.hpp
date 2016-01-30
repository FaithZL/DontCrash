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
    
    inline void setFarthestFlagbyTag(int enemyTag , bool flag){
        _bFarthestFlag[enemyTag] = flag;
    }
    
    inline bool getFarthestFlagbyTag(int enemyTag){
        return _bFarthestFlag[enemyTag];
    }
    
    inline void setDistance(int enemyTag, float distance){
        _preDis[enemyTag] = distance;
    }
    
    inline void setExtraScoreByTag(int enemyTag){
        _extraScore[enemyTag] = 8;
    }
    
    inline float getExtraScoreByTag(int enemyTag){
        return _extraScore[enemyTag];
    }
    
    inline float getPreDistance(int enemyTag){
        return _preDis[enemyTag];
    }
    
    static Car * create(std::string fileName , float originVelo , cocos2d::Vec2 originPos , int direction);
    
    virtual void update(float d);
    
    void updateRadius(float d);
    
    virtual void reset();
    
    virtual void changeTrack();
    
protected:
    
    float _extraScore[3];
    
    float _preDis[3];
    //present whether arrive at farthest distance by enemy tag
    bool _bFarthestFlag[3];
};

#endif /* Car_hpp */
