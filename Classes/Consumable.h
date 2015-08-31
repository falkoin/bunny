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
    static Consumable* create(int taste);
    int getTaste();
private:
    void initOptions(int taste);
    
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
    int _taste;
};

#endif /* defined(__bunny__Consumable__) */
