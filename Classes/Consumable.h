//
//  Consumable.h
//  bunny
//
//  Created by Falko Döhring on 29.08.15.
//
//

#ifndef __bunny__Consumable__
#define __bunny__Consumable__

#include "cocos2d.h"

class Consumable : public cocos2d::Sprite
{
public:
    Consumable();
    virtual ~Consumable();
    static Consumable* create(int taste, int trigger, bool triggered);
    int getTaste();
    int getTrigger();
    void setTriggered(bool triggered);
    bool getTriggered();
    void pushPill();
    bool isBusy();
    void explodeSelf();
    void explodeCallback();
    
private:
    void initOptions(int taste, int trigger, bool triggered);
    bool _triggered;
    
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
    int _taste;
    int _trigger;
    void setBusy();
    bool _busy;
};

#endif /* defined(__bunny__Consumable__) */