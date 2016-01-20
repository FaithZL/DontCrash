//
//  Z_Math.h
//  DontCrash
//
//  Created by SATAN_Z on 16/1/20.
//
//

#ifndef Z_Math_h
#define Z_Math_h

#include "cocos2d.h"
#include "constant.h"

USING_NS_CC;

inline double convertToPI(double angle);

double convertToPI(double angle)
{
    return angle / 180 * PI;
}

inline double convertTo180(double angle);

double convertTo180(double angle)
{
    return angle * 180 / PI;
}

//inline double convertToCC(double angle)
//{
//    
//}
//
//inline double convertToMath(double angle)
//{
//    
//}

inline double getAngle(cocos2d::Vec2 center , cocos2d::Vec2 pos)
{
    double angle;
    if (pos.x == center.x) {
        if (pos.y > center.y) {
            angle = PI / 2;
        }
        else
        {
            angle = - PI / 2;
        }
        return angle;
    }
    angle = atan((pos.y - center.y) / (pos.x - center.x));
    if (pos.x < center.x) {
        angle = angle + PI;
    }
    if (angle < 0) {
        angle = angle + 2 * PI;
    }
    return angle;
}

#endif /* Z_Math_h */
