//
//  Movable.h
//  bunny
//
//  Created by Falko Döhring on 05.09.15.
//
//

#ifndef __bunny__Movable__
#define __bunny__Movable__

#include "cocos2d.h"

class Movable : public cocos2d::Sprite
{
public:
    Movable();
    virtual ~Movable();
    static Movable* create(float speed);
    float getSpeed();
private:
    void initOptions(float speed);
    float _speed;
    
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
};


#endif /* defined(__bunny__Movable__) */
