//
//  Light.cpp
//  platPro
//
//  Created by Falko Döhring on 23.05.15.
//
//

#include "Light.h"
#include "Globals.h"

USING_NS_CC;

Light::Light()
{
}

Light::~Light()
{
}

Light* Light::create(int taste)
{
    Light* pSprite = new Light();
    bool success;
    if (taste == 1)
    {
        success = pSprite->initWithFile("lightPink.png");
        
    } else if (taste == 2)
    {
        success = pSprite->initWithFile("lightCyan.png");
    } else if (taste == 3)
    {
        success = pSprite->initWithFile("light.png");
    }
    else
    {
        success = false;
    }
    
    if (success)
    {
        pSprite->initOptions();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0.5,0.5));
        pSprite->setOpacity(40);
        pSprite->autorelease();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Light::initOptions()
{
    
}