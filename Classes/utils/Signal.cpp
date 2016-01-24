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

void Signal::registerEvent(std::string eventName , Sig_Target pTarget , Sig_SEL pSelector, int priority){
    
    std::map<std::string, std::vector<Sig_struct>>::iterator iter_m = _structMap.find(eventName);
    
    if (iter_m == _structMap.end()) {
        //new
        std::vector<Sig_struct> v_struct;
        _structMap.insert(std::make_pair(eventName, v_struct));
    }
    
    Sig_struct sig_struct = {
        .priority = priority,
        .pTarget = pTarget,
        .pSelector = pSelector
    };
    
    std::vector<Sig_struct> &v_struct = _structMap[eventName];
    std::vector<Sig_struct>::iterator iter_v = v_struct.begin();
    
    while (iter_v != v_struct.end()) {
        if (iter_v->priority < priority) {
            v_struct.insert(iter_v, sig_struct);
            break;
        }
        iter_v ++;
    }
    
    if (iter_v == v_struct.end()) {
        v_struct.push_back(sig_struct);
    }
    
}

void Signal::dispatchEvent(std::string eventName , ...){
    
    va_list args;
    va_start(args, eventName);
    
    std::map<std::string, std::vector<Sig_struct>>::iterator iter_m = _structMap.find(eventName);
    
    if (iter_m != _structMap.end()) {
        
        std::vector<Sig_struct> &v_struct = _structMap[eventName];
        std::vector<Sig_struct>::iterator iter_v = v_struct.begin();
        bool bContinue = true;
        while (iter_v != v_struct.end()) {
            if (bContinue) {
                
            }else{
                break;
            }
        }
    }
    va_end(args);
}

void Signal::removeEvent(std::string eventName, Sig_Target pTarget , Sig_SEL pSelector){
    
    std::vector<Sig_struct> &v_struct = _structMap[eventName];
    std::vector<Sig_struct>::iterator iter;
    for (iter = v_struct.begin() ; iter != v_struct.end() ; iter ++) {
        if (pTarget == iter->pTarget && pSelector == iter->pSelector) {
            v_struct.erase(iter);
            break;
        }
    }
}

void Signal::clearEvent(std::string eventName){
    _structMap[eventName].clear();
}

void Signal::clear(){
    _structMap.clear();
}



