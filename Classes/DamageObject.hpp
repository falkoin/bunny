//
//  DamageObject.hpp
//  bunny
//
//  Created by Falko Döhring on 18.09.15.
//
//

#ifndef DamageObject_hpp
#define DamageObject_hpp

#include "cocos2d.h"

class DamageObject : public cocos2d::Sprite
{
public:
    DamageObject();
    virtual ~DamageObject();
    static DamageObject* create(int taste);
    int getDamageObjectType();
private:
    int _taste;
    void initOptions(int taste);
    CC_SYNTHESIZE(cocos2d::Action*, idleAnimation, IdleAnimation);
    cocos2d::AnimationCache *_idleCache;
    cocos2d::Animation *_idleAnimation;
};


#endif /* DamageObject_hpp */
