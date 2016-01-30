//
//  OverLayer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/30.
//
//

#ifndef OverLayer_hpp
#define OverLayer_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

USING_NS_CC;

class OverLayer : public cocos2d::Layer {
    
public:
    enum CB{
        Share,
        More,
        Rank,
        Fav,
        Reset,
        length
    };
    OverLayer();
    ~OverLayer();
    
    CREATE_FUNC(OverLayer);
    
    void createCallback();
    
    virtual bool init();
    
    void pop();
    
    void pickUp();
    
    void createButtons();
    
    void bindEvent();
    
protected:
    
    std::function<void(Ref *)> _callBack[CB::length];
    
    ui::Button * _btnReset;
    
    ui::Button * _btnMore;
    
    ui::Button * _btnRank;
    
    ui::Button * _btnFav;
    
    ui::Button * _btnShare;
    
};

#endif /* OverLayer_hpp */
