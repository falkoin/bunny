//
//  DamageObject.cpp
//  bunny
//
//  Created by Falko Döhring on 18.09.15.
//
//

#include "DamageObject.hpp"
#include "Globals.h"

USING_NS_CC;

DamageObject::DamageObject()
{
}

DamageObject::~DamageObject()
{
}

DamageObject* DamageObject::create(int taste)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    DamageObject* pSprite = new DamageObject();
    bool success;
    if (taste == 1)
    {
        success = pSprite->initWithSpriteFrameName("lava_0.png");
    }
    else if (taste == 2)
    {
        success = pSprite->initWithSpriteFrameName("scanBot_0.png");
    }
    else if (taste == 3)
    {
        success = pSprite->initWithSpriteFrameName("saw_0.png");
    }
    else if (taste == 4)
    {
        success = pSprite->initWithSpriteFrameName("movingWall.png");
    }
    else
    {
        success = false;
    }
    
    if (success)
    {
        pSprite->initOptions(taste);
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0,0));
        if (taste == 2)
        {
            auto moveBy1 = MoveBy::create(2, Vec2(0,240));
            auto moveBy2 = MoveBy::create(2, Vec2(0,-240));
            pSprite->runAction(RepeatForever::create(Sequence::create(moveBy1, moveBy2, nullptr)));
        }
        pSprite->autorelease();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void DamageObject::initOptions(int taste)
{
    _taste = taste;
    if (taste == 1)
    {
        AnimationCache::getInstance()->addAnimationsWithFile("lava-animations.plist");
        
        // idle animation
        _idleCache = AnimationCache::getInstance();
        _idleAnimation = _idleCache->getAnimation("idle");
        _idleAnimation->setRestoreOriginalFrame(true);
        _idleAnimation->setDelayPerUnit(cocos2d::RandomHelper::random_real(0.1, 0.2));
        
        idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
        idleAnimation->retain();
        runAction(idleAnimation);
    }
    else if (taste == 2)
    {
        AnimationCache::getInstance()->addAnimationsWithFile("scanbot-animations.plist");
        
        // idle animation
        _idleCache = AnimationCache::getInstance();
        _idleAnimation = _idleCache->getAnimation("idle");
        _idleAnimation->setRestoreOriginalFrame(true);
        _idleAnimation->setDelayPerUnit(0.1f);
        
        idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
        idleAnimation->retain();
        runAction(idleAnimation);
    }
    else if (taste == 3)
    {
        AnimationCache::getInstance()->addAnimationsWithFile("saw-animations.plist");
        
        // idle animation
        _idleCache = AnimationCache::getInstance();
        _idleAnimation = _idleCache->getAnimation("idle");
        _idleAnimation->setRestoreOriginalFrame(true);
        _idleAnimation->setDelayPerUnit(0.1f);
        
        idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
        idleAnimation->retain();
        runAction(idleAnimation);
    }
    else if (taste == 4)
    {
        AnimationCache::getInstance()->addAnimationsWithFile("glow-animations.plist");
        this->setColor(Color3B(255,195,0));
        // idle animation
        _idleCache = AnimationCache::getInstance();
        _idleAnimation = _idleCache->getAnimation("idle");
        _idleAnimation->setRestoreOriginalFrame(true);
        _idleAnimation->setDelayPerUnit(0.1f);
        
        idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
        idleAnimation->retain();
        runAction(idleAnimation);
        _damageable = false;
        auto fadeAction = FadeTo::create(2.0f, 0);
        auto delayAction = DelayTime::create(2.0f);
        auto callAction = CallFunc::create([this]() {this->toggleCallback();});
        auto fadeAction2 = FadeTo::create(2.0f, 255);
        auto damageSequence = Sequence::create(fadeAction, delayAction, fadeAction2, callAction, delayAction, callAction, NULL);
        runAction(RepeatForever::create(damageSequence));
        
    }
}

int DamageObject::getDamageObjectType()
{
    return _taste;
}

bool DamageObject::damageable()
{
    return _damageable;
}

void DamageObject::toggleCallback()
{
    _damageable = !_damageable;
}