#include "MainMenuScene.h"
#include "TestScene.h"
#include "Globals.h"
#include "LevelMenuScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
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
    
    auto playItem = MenuItemImage::create("buttonStart.png","buttonStartPressed.png",CC_CALLBACK_1(MainMenuScene::gotToGameScene, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height * 2/3 + origin.y));
    
    auto playItem2 = MenuItemImage::create("buttonHighscore.png","buttonHighscorePressed.png",CC_CALLBACK_1(MainMenuScene::gotToGameScene, this));
    playItem2->setScale(SCALE_FACTOR/3.0f);
    playItem2->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height * 1/3 + origin.y));
    
    auto menu = Menu::create(playItem,playItem2,NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    // sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bloop.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("woooh.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("ouch.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("awesome.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("burn.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jump.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fire.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bounce.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("warp.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("teleport.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
    
//    UserDefault::getInstance()->setFloatForKey("Level001T", 99999.99);
//    UserDefault::getInstance()->setFloatForKey("Level002T", 99999.99);
//    UserDefault::getInstance()->setFloatForKey("Level003T", 99999.99);
//    UserDefault::getInstance()->setFloatForKey("Level004T", 99999.99);
//    UserDefault::getInstance()->setFloatForKey("Level005T", 99999.99);
//    UserDefault::getInstance()->setIntegerForKey("Level001HS", 0);
//    UserDefault::getInstance()->setIntegerForKey("Level002HS", 0);
//    UserDefault::getInstance()->setIntegerForKey("Level003HS", 0);
//    UserDefault::getInstance()->setIntegerForKey("Level004HS", 0);
//    UserDefault::getInstance()->setIntegerForKey("Level005HS", 0);
    
    
    
    
    
    return true;
}

void MainMenuScene::gotToGameScene(Ref *sender)
{
    auto scene = LevelMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}
