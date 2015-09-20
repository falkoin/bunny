//
//  Explosion.hpp
//  bunny
//
//  Created by Falko Döhring on 19.09.15.
//
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include "cocos2d.h"

class Explosion : public cocos2d::Sprite
{
public:
    Explosion();
    virtual ~Explosion();
    static Explosion* create();
private:
    void initOptions();
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
    void removeExplosion();
};

#endif /* defined(__bunny__FallingObject__) */

