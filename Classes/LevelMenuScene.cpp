#include "LevelMenuScene.h"
#include "TestScene.h"
#include "TestSceneTwo.h"
#include "TestSceneThree.h"
#include "Globals.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* LevelMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelMenuScene::init()
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
    
    // sound
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bloop.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("woooh.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("ouch.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    auto playItem = MenuItemImage::create("lvl01.png","lvl01pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelOne, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height * 3/4 + origin.y));
    
    auto playItem2 = MenuItemImage::create("lvl02.png","lvl02pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelTwo, this));
    playItem2->setScale(SCALE_FACTOR/3.0f);
    playItem2->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height * 2/4 + origin.y));
    
    auto playItem3 = MenuItemImage::create("lvl03.png","lvl03pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelThree, this));
    playItem3->setScale(SCALE_FACTOR/3.0f);
    playItem3->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height * 1/4 + origin.y));
    
    auto menu = Menu::create(playItem, playItem2, playItem3, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    
    
    
    return true;
}

void LevelMenuScene::goToLevelOne(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 1);
    auto scene = TestScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}

void LevelMenuScene::goToLevelTwo(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 2);
    auto scene = TestSceneTwo::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}

void LevelMenuScene::goToLevelThree(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 3);
    auto scene = TestSceneThree::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}
