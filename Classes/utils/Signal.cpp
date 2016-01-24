//
//  Signal.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/23.
//
//

#include "Signal.hpp"

Signal::Signal(){
    
}

Signal::~Signal(){
    clear();
}

bool Signal::init(){
    
    return true;
}

void Signal::registerEvent(std::string eventName, std::function<bool ()> callback, int priority){
    
    auto iter = _callbackMap.find(eventName);
    
    if (iter == _callbackMap.end()) {
        //new
        std::vector<type_cb> v;
        _callbackMap.insert(std::make_pair(eventName , v));
        
        std::vector<int> v2;
        _priorityMap.insert(std::make_pair(eventName, v2));
    }
    
    auto v_callback = _callbackMap[eventName];
    auto v_priority = _priorityMap[eventName];
    
}

void Signal::dispatchEvent(std::string eventName){
    
    auto iter = _callbackMap.find(eventName);
    
    if (iter != _callbackMap.end()) {
        auto v_callback = _callbackMap[eventName];
        bool bContinue = true;
        for (auto iter = v_callback.begin() ; iter != v_callback.end() ; iter ++) {
            if (bContinue) {
                bContinue = (*iter)();
            }else{
                break;
            }
        }
    }
}

void Signal::removeEvent(std::string eventName, std::function<bool ()> * callback){
    auto v_callback = _callbackMap[eventName];
    auto v_priority = _priorityMap[eventName];
    
    std::vector<int>::iterator iter2 = v_priority.begin();
    
    for (auto iter = v_callback.begin() ; iter != v_callback.end() ; iter++ , iter2 ++ ) {
        if (&(*iter) == callback) {
            v_priority.erase(iter2);
            v_callback.erase(iter);
            break;
        }
    }
}

void Signal::clearEvent(std::string eventName){
    auto v_callback = _callbackMap[eventName];
    v_callback.clear();
    
    auto v_priority = _priorityMap[eventName];
    v_priority.clear();
}

void Signal::clear(){
    _priorityMap.clear();
    _callbackMap.clear();
}