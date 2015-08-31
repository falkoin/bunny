//
//  Player.h
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#ifndef __bunny__Player__
#define __bunny__Player__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
    Player();
    virtual ~Player();
    static Player* create();
    cocos2d::Vec2 getPlayerVelocity();
    void moveUp();
    void moveUpDouble();
    void moveLeft();
    void moveRight();
    void stop();
    void setPlayerVelocity(cocos2d::Vec2 velocity);
    bool grounded;
    
    enum State {
        Idle, Jumping, Dead
    };
    State state;
    
private:
    void initOptions();
    cocos2d::Vec2 _velocity;
    
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
};


#endif /* defined(__bunny__Player__) */
