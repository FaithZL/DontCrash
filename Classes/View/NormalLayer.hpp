//
//  NormalLayer.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/30.
//
//

#ifndef NormalLayer_hpp
#define NormalLayer_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
USING_NS_CC;
class NormalLayer : public cocos2d::Layer {
    
public:
    
    NormalLayer();
    ~NormalLayer();
    
    enum CB{
        pause,
        start,
        length
    };
	
    virtual bool init();
    
    CREATE_FUNC(NormalLayer);
    
    void createCallback();
    
    void createWidget();
    
    void bindEvent();
    
    void pop();
    
    void pickUp();
    
    bool refreshScore(va_list args);
	
	void playRewardEff();
    
protected:
    
    std::function<void(Ref *)> _callBack[CB::length];
    
    ui::Button * _btnStart;
    
    ui::Button * _btnPause;
    
    cocos2d::Label * _lblScore;
    
    
};

#endif /* NormalLayer_hpp */
