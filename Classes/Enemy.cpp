//
//  Player.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
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
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Enemy::initOptions()
{
}