//
//  Player.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "Player.h"
#include "Globals.h"
#include "GameScene.h"

USING_NS_CC;

Player::Player()
{
}

Player::~Player()
{
}

Player* Player::create()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Player* pSprite = new Player();
    
    if (pSprite->initWithSpriteFrameName("player.png"))
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

void Player::initOptions()
{
    _velocity = Point(0,0);
    AnimationCache::getInstance()->addAnimationsWithFile("player-animations.plist");
    
    // idle animation
    _idleCache = AnimationCache::getInstance();
    _idleAnimation = _idleCache->getAnimation("idle");
    _idleAnimation->setRestoreOriginalFrame(true);
    
    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
    idleAnimation->retain();
    runAction(idleAnimation);
    
}

void Player::setPlayerVelocity(cocos2d::Vec2 velocity)
{
    _velocity = velocity;
}

Vec2 Player::getPlayerVelocity()
{
    return _velocity;
}

void Player::moveUp()
{
    _velocity.y = PLAYER_MAX_JUMP_VELOCITY * SCALE_FACTOR;
}
void Player::moveUpDouble()
{
    _velocity.y = PLAYER_MAX_JUMP_VELOCITY * 2 * SCALE_FACTOR;
}

void Player::moveRight()
{
//    _velocity.x = +PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    _velocity.x = _velocity.x + 0.125f;
    if (_velocity.x >= PLAYER_MAX_VELOCITY * SCALE_FACTOR)
    {
        _velocity.x = PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    }
}

void Player::moveLeft()
{
//    _velocity.x = -PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    _velocity.x = _velocity.x - 0.125f;
    if (_velocity.x <= -PLAYER_MAX_VELOCITY * SCALE_FACTOR)
    {
        _velocity.x = -PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    }

}

void Player::stop()
{
    _velocity.x = 0.0f;
}