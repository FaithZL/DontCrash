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

void Signal::registerEvent(std::string eventName, Signal_cb callback, int priority){
    
    std::map<std::string, std::vector<Signal_cb>>::iterator iter = _callbackMap.find(eventName);
    
    if (iter == _callbackMap.end()) {
        //new
        std::vector<Signal_cb> v_callback;
        _callbackMap.insert(std::make_pair(eventName , v_callback));
        
        std::vector<int> v_priority;
        _priorityMap.insert(std::make_pair(eventName, v_priority));
    }
    
    std::vector<Signal_cb> &v_callback = _callbackMap[eventName];
    std::vector<int> &v_priority = _priorityMap[eventName];
    
    std::vector<Signal_cb>::iterator iter_v_c = v_callback.begin();
    std::vector<int>::iterator iter_v_p= v_priority.begin();
    
    while (iter_v_p != v_priority.end()) {
    
        if (priority < * iter_v_p) {
            v_priority.insert(iter_v_p, priority);
            v_callback.insert(iter_v_c, callback);
            break;
        }
        iter_v_c ++;
        iter_v_p ++;
    }
    if (iter_v_p == v_priority.end()) {
        v_priority.push_back(priority);
        v_callback.push_back(callback);
    }
}

void Signal::dispatchEvent(std::string eventName){
    
    std::map<std::string, std::vector<Signal_cb>>::iterator iter_m_c = _callbackMap.find(eventName);
    
    if (iter_m_c != _callbackMap.end()) {
        
        std::vector<Signal_cb> v_callback = _callbackMap[eventName];
        bool bContinue = true;
        for (std::vector<Signal_cb>::iterator iter = v_callback.begin() ; iter != v_callback.end() ; iter ++) {
            if (bContinue) {
                Signal_cb pfun = static_cast<Signal_cb>(*iter);
//                bContinue = (*pfun)();
            }else{
                break;
            }
        }
    }
}

void Signal::removeEvent(std::string eventName, Signal_cb callback){
    
    std::vector<Signal_cb> &v_callback = _callbackMap[eventName];
    std::vector<int> &v_priority = _priorityMap[eventName];

    std::vector<int>::iterator iter_v_p = v_priority.begin();
    std::vector<Signal_cb>::iterator iter_v_c;
    for (iter_v_c = v_callback.begin() ; iter_v_c != v_callback.end() ; iter_v_c++ , iter_v_p ++ ) {
        if (*iter_v_c == callback) {
            v_priority.erase(iter_v_p);
            v_callback.erase(iter_v_c);
            break;
        }
    }
}

void Signal::clearEvent(std::string eventName){
    _callbackMap[eventName].clear();
    
    _targetMap[eventName].clear();
    
    _priorityMap[eventName].clear();
}

void Signal::clear(){
    _priorityMap.clear();
    _callbackMap.clear();
    _targetMap.clear();
}



