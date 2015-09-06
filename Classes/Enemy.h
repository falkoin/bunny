//
//  Enemy.h
//  bunny
//
//  Created by Falko Döhring on 05.09.15.
//
//

#ifndef __bunny__Enemy__
#define __bunny__Enemy__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    Enemy();
    virtual ~Enemy();
    static Enemy* create();
    cocos2d::Vec2 getEnemyVelocity();
    void setEnemyVelocity(cocos2d::Vec2 velocity);
    
    enum State {
        Idle, Jumping, Dead, Win
    };
    State state;
    
private:
    void initOptions();
    cocos2d::Vec2 _velocity;
    
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
    CC_SYNTHESIZE(cocos2d::Action*, happyAnimation, HappyAnimation);
    cocos2d::AnimationCache *_happyCache;
    cocos2d::Animation *_happyAnimation;
    CC_SYNTHESIZE(cocos2d::Action*, winAnimation, WinAnimation);
    cocos2d::AnimationCache *_winCache;
    cocos2d::Animation *_winAnimation;
};


#endif /* defined(__bunny__Enemy__) */
