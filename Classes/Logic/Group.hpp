//
//  Group.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/25.
//
//

#ifndef Group_hpp
#define Group_hpp

#include "cocos2d.h"

class Enemy;

class Group : cocos2d::Ref {
public:
    Group();
    ~Group();
    
    bool init();
    
    CC_SYNTHESIZE(cocos2d::Vector<Enemy *> * , _enemies, Enemies);
    
    CREATE_FUNC(Group);
    
protected:
};



#endif /* Group_hpp */
