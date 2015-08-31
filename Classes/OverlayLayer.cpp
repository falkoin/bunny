//
//  OverlayLayer.cpp
//  platPro
//
//  Created by Falko Döhring on 23.05.15.
//
//

#include "OverlayLayer.h"
#include "MainMenuScene.h"
#include "TestScene.h"
#include "Globals.h"

bool OverlayLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(100, 0, 0, 0)))
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    _trialEndLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","",CCTextAlignment::CENTER);
    _trialEndLabel->setColor(cocos2d::Color3B(0, 0, 0));
    _trialEndLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f,origin.y + visibleSize.height*(0.5f)));
    _trialEndLabel->setAnchorPoint(Point(0.5,0.5));
    _trialEndLabel->setScale(SCALE_FACTOR/3);
    _trialEndLabel->getTexture()->setAliasTexParameters();
    _trialEndLabel->setGlobalZOrder(9999);
    _trialEndLabel->retain();
    
    _trialWinLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","",CCTextAlignment::CENTER);
    _trialWinLabel->setColor(cocos2d::Color3B(0, 0, 0));
    _trialWinLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f,origin.y + visibleSize.height*(0.5f)));
    _trialWinLabel->setAnchorPoint(Point(0.5,0.5));
    _trialWinLabel->setScale(SCALE_FACTOR/3);
    _trialWinLabel->getTexture()->setAliasTexParameters();
    _trialWinLabel->setGlobalZOrder(9999);
    _trialWinLabel->retain();
    
    _scoreLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","");
    _scoreLabel->setColor(cocos2d::Color3B(0, 0, 0));
    _scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.80f,origin.y + visibleSize.height*(0.95f)));
    _scoreLabel->setAnchorPoint(Point(0.0,0.0));
    _scoreLabel->setScale(SCALE_FACTOR/6.0f);
    _scoreLabel->getTexture()->setAliasTexParameters();
    _scoreLabel->setGlobalZOrder(9999);
    _scoreLabel->retain();
    addChild(_scoreLabel);
    return true;
}

void OverlayLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    LayerColor::draw(renderer, transform, flags);
}


void OverlayLayer::drawEndMessage()
{
    _trialEndLabel->Label::setString("Game Over \nTouch to continue");
    this->addChild(_trialEndLabel, 1001);
}

void OverlayLayer::drawWinMessage()
{
    _trialWinLabel->Label::setString("Success!\n You won! \nTouch to continue");
    this->addChild(_trialWinLabel, 1001);
}

void OverlayLayer::updateScore(int score)
{
    _scoreLabel->Label::setString("Score: "+std::to_string(score));
}

