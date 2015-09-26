//
//  Consumable.cpp
//  bunny
//
//  Created by Falko Döhring on 29.08.15.
//
//

#include "Consumable.h"
#include "Globals.h"

USING_NS_CC;

Consumable::Consumable()
{
}

Consumable::~Consumable()
{
}

Consumable* Consumable::create(int taste, int trigger, bool triggered)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Consumable* pSprite = new Consumable();
    
    if (pSprite->initWithSpriteFrameName("pill_00.png"))
    {
        pSprite->initOptions(taste, trigger, triggered);
        pSprite->autorelease();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0,0));
        if (triggered)
        {
            pSprite->setVisible(true);
        }
        else
        {
            pSprite->setVisible(false);
        }
            
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Consumable::initOptions(int taste, int trigger, bool triggered)
{
    _taste = taste;
    _trigger = trigger;
    _triggered = triggered;
    switch (_taste) {
        case 1:
            AnimationCache::getInstance()->addAnimationsWithFile("consumable-animations.plist");
            break;
        case 2:
            AnimationCache::getInstance()->addAnimationsWithFile("highJump-animations.plist");
            break;
        case 3:
            AnimationCache::getInstance()->addAnimationsWithFile("doublePoints-animations.plist");
            break;
        case 4:
            AnimationCache::getInstance()->addAnimationsWithFile("trigger-animations.plist");
            break;
        default:
            break;
    }
    // idle animation
    _idleCache = AnimationCache::getInstance();
    _idleAnimation = _idleCache->getAnimation("idle");
    _idleAnimation->setRestoreOriginalFrame(true);
    _idleAnimation->setDelayPerUnit(cocos2d::RandomHelper::random_real(0.1, 0.3));
    
    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
    idleAnimation->retain();
    runAction(idleAnimation);
    
}

int Consumable::getTaste()
{
    return _taste;
}

int Consumable::getTrigger()
{
    return _trigger;
}

void Consumable::setTriggered(bool triggered)
{
    _triggered = triggered;
}

bool Consumable::getTriggered()
{
    return _triggered;
}