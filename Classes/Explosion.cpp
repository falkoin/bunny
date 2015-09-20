//
//  Explosion.cpp
//  bunny
//
//  Created by Falko Döhring on 19.09.15.
//
//

#include "Explosion.hpp"
#include "Globals.h"

USING_NS_CC;

Explosion::Explosion()
{
}

Explosion::~Explosion()
{
}

Explosion* Explosion::create()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Explosion* pSprite = new Explosion();
    bool success;
    success = pSprite->initWithSpriteFrameName("explosion_0.png");
    
    
    if (success)
    {
        pSprite->initOptions();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR*2);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0.5,0.5));
        pSprite->autorelease();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Explosion::initOptions()
{
    
    AnimationCache::getInstance()->addAnimationsWithFile("explosion-animations.plist");
    
    // idle animation
    _idleCache = AnimationCache::getInstance();
    _idleAnimation = _idleCache->getAnimation("idle");
    _idleAnimation->setRestoreOriginalFrame(false);
    _idleAnimation->setDelayPerUnit(0.05f);
    
    Animate* idleAnimation2 = Animate::create(_idleAnimation);
    idleAnimation2->retain();
    auto fadeAction = FadeOut::create(0.5);
    auto removeFunc = RemoveSelf::create();
    runAction(Sequence::create(idleAnimation2, fadeAction, removeFunc, NULL));
    
}

void Explosion::removeExplosion()
{
    this->removeFromParent();
}
