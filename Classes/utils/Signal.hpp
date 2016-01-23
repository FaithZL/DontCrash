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

class Signal :public cocos2d::Ref{
    
public:
    Signal();
    
    ~Signal();
    
    virtual bool init();
    
    void registerEvent(std::string eventName , std::function<bool()> callback, int priority);
    
    void dispatchEvent(std::string eventName);
    
    void removeEvent(std::string eventName , std::function<bool()> callback);
    
    void clearEvent(std::string eventName);
    
    void clear();
    
    CREATE_FUNC(Signal);
    
protected:
    
    std::map<std::string , std::vector<std::function<bool()>>> _callbackMap;
    
    std::map<std::string, std::vector<int>> _priorityMap;
};

#endif /* Signal_hpp */
