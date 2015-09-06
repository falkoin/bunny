//
//  Enemy.cpp
//  bunny
//
//  Created by Falko Döhring on 05.09.15.
//
//

#include "Enemy.h"
#include "Globals.h"


USING_NS_CC;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy* Enemy::create()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Enemy* pSprite = new Enemy();
    
    if (pSprite->initWithSpriteFrameName("playerIdle.png"))
    {
        pSprite->initOptions();
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

void Enemy::initOptions()
{
    state = State::Idle;
    _velocity = Point(0,0);
    AnimationCache::getInstance()->addAnimationsWithFile("player-animations.plist");
    
    // idle animation
    _idleCache = AnimationCache::getInstance();
    _idleAnimation = _idleCache->getAnimation("idle");
    _idleAnimation->setRestoreOriginalFrame(false);
    
    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
    idleAnimation->retain();
    runAction(idleAnimation);
    
    // happy animation
    _happyCache = AnimationCache::getInstance();
    _happyAnimation = _happyCache->getAnimation("happy");
    _happyAnimation->setRestoreOriginalFrame(false);
    
    happyAnimation = Animate::create(_happyAnimation);
    happyAnimation->retain();
    
    // win animation
    _winCache = AnimationCache::getInstance();
    _winAnimation = _winCache->getAnimation("win");
    _winAnimation->setRestoreOriginalFrame(true);
    
    winAnimation = RepeatForever::create(Animate::create(_winAnimation));
    winAnimation->retain();
    
}

void Enemy::setEnemyVelocity(cocos2d::Vec2 velocity)
{
    _velocity = velocity;
}

Vec2 Enemy::getEnemyVelocity()
{
    return _velocity;
}