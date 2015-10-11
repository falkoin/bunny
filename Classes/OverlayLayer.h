//
//  OverlayLayer.h
//  platPro
//
//  Created by Falko Döhring on 23.05.15.
//
//

#ifndef __platPro__OverlayLayer__
#define __platPro__OverlayLayer__

#include "cocos2d.h"
USING_NS_CC;

class OverlayLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(OverlayLayer);
    
//    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
    inline virtual cocos2d::Label* getMessageLabel() { return _trialEndLabel; };
//    void setLabel(std::string time);
    void drawEndMessage(std::string message);
    void updateScore(int score);
    void updateTimer(std::string timer);
    void shouOut(std::string shoutoutText);
private:
    cocos2d::Label* _trialEndLabel;
    cocos2d::Label* _trialWinLabel;
    cocos2d::Label* _shoutWinLabel;
    cocos2d::Label* _scoreLabel;
    cocos2d::Label* _timerLabel;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    void drawHackerFont(std::string label);
    bool printReady;
    
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
};

#endif /* defined(__platPro__OverlayLayer__) */
