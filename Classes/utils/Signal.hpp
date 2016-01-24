//
//  Signal.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/23.
//
//

#ifndef Signal_hpp
#define Signal_hpp

#include "cocos2d.h"

//typedef bool (* type_cb)();

typedef std::function<bool()> * type_cb;

typedef bool (cocos2d::Ref::*Signal_cb)(int arg , ...);


class Signal :public cocos2d::Ref{
    
public:
    Signal();
    
    ~Signal();
    
    virtual bool init();
    
    void registerEvent(std::string eventName , Signal_cb callback, int priority);
    
    void dispatchEvent(std::string eventName);
    
    void removeEvent(std::string eventName , Signal_cb callback);
    
    void clearEvent(std::string eventName);
    
    void clear();
    
    CREATE_FUNC(Signal);
    
protected:
    
    std::map<std::string , std::vector<Signal_cb>> _callbackMap;
    
    std::map<std::string , std::vector<Ref *>> _targetMap;
    
    std::map<std::string, std::vector<int>> _priorityMap;
};

#endif /* Signal_hpp */
