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
    
    std::map<std::string, std::vector<type_cb>>::iterator iter = _callbackMap.find(eventName);
    
    if (iter == _callbackMap.end()) {
        //new
        std::vector<type_cb> v_callback;
        _callbackMap.insert(std::make_pair(eventName , v_callback));
        
        std::vector<int> v_priority;
        _priorityMap.insert(std::make_pair(eventName, v_priority));
    }
    
    std::vector<type_cb> v_callback = _callbackMap[eventName];
    std::vector<int> v_priority = _priorityMap[eventName];
    
    std::vector<type_cb>::iterator iter_v_c = v_callback.begin();
    std::vector<int>::iterator iter_v_p= v_priority.begin();
    
    while (iter_v_p != v_priority.end()) {
        if (priority > * iter_v_p) {
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
    
    std::map<std::string, std::vector<type_cb>>::iterator iter = _callbackMap.find(eventName);
    
    if (iter != _callbackMap.end()) {
        std::vector<type_cb> v_callback = _callbackMap[eventName];
        bool bContinue = true;
        for (std::vector<type_cb>::iterator iter = v_callback.begin() ; iter != v_callback.end() ; iter ++) {
            if (bContinue) {
                bContinue = (*iter)();
            }else{
                break;
            }
        }
    }
}

void Signal::removeEvent(std::string eventName, std::function<bool ()> * callback){
    std::vector<type_cb> v_callback = _callbackMap[eventName];
    std::vector<int> v_priority = _priorityMap[eventName];
    
    std::vector<int>::iterator iter_v_p = v_priority.begin();
    std::vector<type_cb>::iterator iter_v_c;
    for (iter_v_c = v_callback.begin() ; iter_v_c != v_callback.end() ; iter_v_c++ , iter_v_p ++ ) {
        if (&(*iter_v_c) == callback) {
            v_priority.erase(iter_v_p);
            v_callback.erase(iter_v_c);
            break;
        }
    }
}

void Signal::clearEvent(std::string eventName){
    std::vector<type_cb> v_callback = _callbackMap[eventName];
    v_callback.clear();
    
    std::vector<int> v_priority = _priorityMap[eventName];
    v_priority.clear();
}

void Signal::clear(){
    _priorityMap.clear();
    _callbackMap.clear();
}