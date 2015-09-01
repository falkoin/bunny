#include "MainMenuScene.h"
#include "TestScene.h"
#include "Globals.h"
#include "LevelMenuScene.h"


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
    
    auto playItem = MenuItemImage::create("title.png","titleClicked.png",CC_CALLBACK_1(MainMenuScene::gotToGameScene, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto menu = Menu::create(playItem,NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    
    
    
    return true;
}

void MainMenuScene::gotToGameScene(Ref *sender)
{
    auto scene = LevelMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}
