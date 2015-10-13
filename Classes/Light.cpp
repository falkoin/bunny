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
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(220, 43, 220));
        
    }
    else if (taste == 2)
    {
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(26, 220, 220));
    }
    else if (taste == 3)
    {
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(43, 220,54));
    }
    else if (taste == 4)
    {
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(245, 220, 0));
    }
    else if (taste == 5)
    {
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(255, 180, 20));
        
    }
    else if (taste == 6)
    {
        success = pSprite->initWithFile("lightWhite.png");
        pSprite->setColor(Color3B(135, 255, 171));
        
    }
    else if (taste == 9)
    {
    success = pSprite->initWithFile("lightWhite.png");
    }
    else
    {
        success = false;
        log("Missing Light PNG");
    }
    
    if (success)
    {
        pSprite->initOptions();
        pSprite->getTexture()->setAliasTexParameters();
        if (taste != 6)
            pSprite->setScale(SCALE_FACTOR);
        else
            pSprite->setScale(SCALE_FACTOR*0.5);
 
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0.5,0.5));
        pSprite->setOpacity(60);
        pSprite->autorelease();
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Light::initOptions()
{
    
}