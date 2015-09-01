#include "LevelMenuScene.h"
#include "TestScene.h"
#include "TestSceneTwo.h"
#include "Globals.h"


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
    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    auto playItem = MenuItemImage::create("title.png","titleClicked.png",CC_CALLBACK_1(LevelMenuScene::goToLevelOne, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto playItem2 = MenuItemImage::create("title.png","titleClicked.png",CC_CALLBACK_1(LevelMenuScene::goToLevelTwo, this));
    playItem2->setScale(SCALE_FACTOR/3.0f);
    playItem2->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    
    auto menu = Menu::create(playItem, playItem2, NULL);
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
