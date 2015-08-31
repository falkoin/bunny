//
//  GameOverScene.cpp
//  bunny
//
//  Created by Falko Döhring on 29.08.15.
//
//

#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "TestScene.h"
#include "Globals.h"


USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setProjection(cocos2d::DisplayLinkDirector::Projection::_2D);
    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    auto playItem = MenuItemImage::create("retry.png","retryPressed.png",CC_CALLBACK_1(GameOverScene::gotToGameScene, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto playItem2 = MenuItemImage::create("back.png","backPressed.png",CC_CALLBACK_1(GameOverScene::gotToMenuScene, this));
    playItem2->setScale(SCALE_FACTOR/3.0f);
    playItem2->setPosition(Point( visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto menu = Menu::create(playItem,playItem2,NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    
    
    
    return true;
}

void GameOverScene::gotToGameScene(Ref *sender)
{
    auto scene = TestScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

void GameOverScene::gotToMenuScene(Ref *sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}
