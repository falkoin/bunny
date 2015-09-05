//
//  Movable.cpp
//  bunny
//
//  Created by Falko Döhring on 05.09.15.
//
//

#include "Movable.h"
#include "Globals.h"

USING_NS_CC;

Movable::Movable()
{
}

Movable::~Movable()
{
}

Movable* Movable::create(float speed)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Movable* pSprite = new Movable();
    
    if (pSprite->initWithSpriteFrameName("cloud.png"))
    {
        pSprite->initOptions(speed);
        pSprite->autorelease();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0,0));
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Movable::initOptions(float speed)
{
    //    AnimationCache::getInstance()->addAnimationsWithFile("consumable-animations.plist");
    
    // idle animation
    _speed = speed;
//    _idleCache = AnimationCache::getInstance();
//    _idleAnimation = _idleCache->getAnimation("idle");
//    _idleAnimation->setRestoreOriginalFrame(true);
//    _idleAnimation->setDelayPerUnit(cocos2d::RandomHelper::random_real(0.1, 0.3));
//    
//    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
//    idleAnimation->retain();
//    runAction(idleAnimation);
    
}

float Movable::getSpeed()
{
    return _speed;
}

