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
    bool spriteLoad;
    switch (taste) {
        case 1:
            spriteLoad = pSprite->initWithSpriteFrameName("pillPink.png");
            break;
        case 2:
            spriteLoad = pSprite->initWithSpriteFrameName("pillCyan.png");
            break;
        case 3:
            spriteLoad = pSprite->initWithSpriteFrameName("pillGreen.png");
            break;
        case 4:
            spriteLoad = pSprite->initWithSpriteFrameName("pillYellow.png");
            break;
        case 5:
            spriteLoad = pSprite->initWithSpriteFrameName("pillTemplate.png");
            pSprite->setColor(Color3B(255, 180, 20));
            break;
            
        default:
            break;
    }
    
    if (spriteLoad)
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
//    switch (_taste) {
//        case 1:
//            AnimationCache::getInstance()->addAnimationsWithFile("consumable-animations.plist");
//            break;
//        case 2:
//            AnimationCache::getInstance()->addAnimationsWithFile("highJump-animations.plist");
//            break;
//        case 3:
//            AnimationCache::getInstance()->addAnimationsWithFile("doublePoints-animations.plist");
//            break;
//        case 4:
//            AnimationCache::getInstance()->addAnimationsWithFile("trigger-animations.plist");
//            break;
//        default:
//            break;
//    }
//    // idle animation
//    _idleCache = AnimationCache::getInstance();
//    _idleAnimation = _idleCache->getAnimation("idle");
//    _idleAnimation->setRestoreOriginalFrame(true);
//    _idleAnimation->setDelayPerUnit(cocos2d::RandomHelper::random_real(0.1, 0.3));
//    
//    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
//    idleAnimation->retain();
//    runAction(idleAnimation);
    if (taste != 5)
    {
        float moveDuration = cocos2d::RandomHelper::random_real(0.7, 1.1);
        auto moveBy1 = MoveBy::create(moveDuration, Vec2(0,20));
        auto moveBy2 = MoveBy::create(moveDuration, Vec2(0,-20));
        this->runAction(RepeatForever::create(Sequence::create(moveBy1, moveBy2, nullptr)));
    }
    
    
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

void Consumable::pushPill()
{
    if (!_busy)
    {
        _busy = true;
        auto moveBy1 = MoveBy::create(0.1, Vec2(0,-4*SCALE_FACTOR));
        auto moveBy2 = MoveBy::create(0.1, Vec2(0,4*SCALE_FACTOR));
        auto setVar  = CallFunc::create([this]() {this->setBusy();});
        auto setDelay = DelayTime::create(0.8);
        this->runAction(Sequence::create(moveBy1, moveBy2, setVar, setDelay, nullptr));
    }
}

void Consumable::setBusy()
{
    _busy = false;
}

bool Consumable::isBusy()
{
    return _busy;
}