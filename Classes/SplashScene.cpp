#include "SplashScene.h"
#include "LevelMenuScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->scheduleOnce(schedule_selector(SplashScene::goToMainMenuScene), 0.5f);
    
    auto backgroundSprite = Sprite::create("startUp.png");
    backgroundSprite->setPosition(Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);
    
    return true;
}

void SplashScene::goToMainMenuScene(float dt)
{
    auto scene = LevelMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}