//
//  TestSceneTwo.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "TestSceneTwo.h"
#include "GameScene.h"
#include "Level.h"
#include "Globals.h"
#include "OverlayLayer.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* TestSceneTwo::createScene()
{
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestSceneTwo::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSceneTwo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setProjection(cocos2d::DisplayLinkDirector::Projection::_2D);
    // map
    level = new Level();
    level->loadMap("testLevel2.tmx",this);
    level->getMap()->setScale(SCALE_FACTOR);
    this->addChild(level->getMap(),-1);
    auto bg = level->getMap()->getLayer("background");
    bg->setGlobalZOrder(1);
    auto walls = level->getMap()->getLayer("walls");
    walls->setGlobalZOrder(4);
    

    // level objects
    auto *levelObject = level->getMap()->getObjectGroup("objects");
    if(levelObject == NULL){
        log("tile map has no level object layer");
        return false;
    }
    
    ValueVector jumpPosition = levelObject->getObjects();
    for (auto current : jumpPosition)
    {
        float x = current.asValueMap()["x"].asFloat();
        float y = current.asValueMap()["y"].asFloat();
        int taste = current.asValueMap()["taste"].asInt();
        pill = Consumable::create(taste);
        pill->setTag(taste);
        pill->retain();
        pill->setPosition(Point(x*SCALE_FACTOR,y*SCALE_FACTOR));
        addChild(pill);
        pill->setGlobalZOrder(16);
        pillVec.pushBack(pill);
    }
    
    // parallax
    parallaxOne = Sprite::create("parallax21.png");
    parallaxOne->setGlobalZOrder(2);
    parallaxOne->setScale(SCALE_FACTOR);
    parallaxOne->getTexture()->setAliasTexParameters();
    parallaxOne->setPosition(Point(128*16*SCALE_FACTOR-parallaxOne->getContentSize().width*0.5*SCALE_FACTOR,visibleSize.height*0.5+origin.y));
    parallaxOne->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxOne);
    
    parallaxTwo = Sprite::create("parallax22.png");
    parallaxTwo->setGlobalZOrder(3);
    parallaxTwo->setScale(SCALE_FACTOR);
    parallaxTwo->getTexture()->setAliasTexParameters();
    parallaxTwo->setPosition(Point(128*16*SCALE_FACTOR-parallaxOne->getContentSize().width*0.5*SCALE_FACTOR,visibleSize.height*0.5+origin.y));
    parallaxTwo->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxTwo);
    
    // player
    player = Player::create();
    player->retain();
    this->addChild(player);
    player->setPosition(level->tileCoordinateToPosition(Point(120,1)));
    player->setGlobalZOrder(15);
    
    // camera
    cameraTarget = Sprite::create();
    cameraTarget->retain();
    addChild(cameraTarget);
    cameraTarget->setPositionX(visibleSize.width*0.5f+origin.x);
    cameraTarget->setPositionY(visibleSize.height*0.5f+origin.y);
    
    camera = Follow::create(cameraTarget);
    camera->retain();
    this->runAction(camera);
    
    // shader
    _shadowLayer = ShadowLayer::create();
    this->addChild(_shadowLayer);
    _shadowLayer->setGlobalZOrder(999);
    _shadowLayer->setAnchorPoint(Point(0.5, 0.5));
    lastPoint = Point(0,0);
    
    // Overlay
    _hud = OverlayLayer::create();
    this->addChild(_hud);
    _hud->setGlobalZOrder(1005);
    _hud->setAnchorPoint(Point(0.5, 0.5));
    
    // touch
    _touchEnabled = true;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TestSceneTwo::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->schedule(schedule_selector(TestSceneTwo::update), 0.01f);
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(TestSceneTwo::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Device::setAccelerometerInterval(1/60);
    
    // parameters
    score = 0;
    _win = false;
    lastPlayerPosition = player->getPosition();
    
    this->scheduleUpdate();
    return true;
}