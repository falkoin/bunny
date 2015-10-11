//
//  TestSceneThree.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "TestSceneThree.h"
#include "GameScene.h"
#include "Level.h"
#include "Globals.h"
#include "OverlayLayer.h"
#include "MainMenuScene.h"
#include "Light.h"

USING_NS_CC;

Scene* TestSceneThree::createScene()
{
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestSceneThree::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSceneThree::init()
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
    level->loadMap("level3.tmx",this);
    level->getMap()->setScale(SCALE_FACTOR);
    this->addChild(level->getMap(),-1);
    auto bg = level->getMap()->getLayer("background");
    bg->setGlobalZOrder(Z_BG);
    auto walls = level->getMap()->getLayer("walls");
    walls->setGlobalZOrder(Z_WALLS);
    auto wallShadow = level->getMap()->getLayer("wallShadow");
    wallShadow->setGlobalZOrder(Z_WALLS);
    
    // level objects
    auto *levelObject = level->getMap()->getObjectGroup("objects");
    if(levelObject == NULL){
        log("tile map has no level object layer");
        return false;
    }
    
    ValueVector jumpPosition = levelObject->getObjects();
    for (auto current : jumpPosition)
    {
        bool triggered;
        float x = current.asValueMap()["x"].asFloat();
        float y = current.asValueMap()["y"].asFloat();
        int taste = current.asValueMap()["taste"].asInt();
        int trigger = current.asValueMap()["trigger"].asInt();
        if (trigger != 0)
            triggered = false;
        else
            triggered = true;
        auto pill = Consumable::create(taste,trigger,triggered);
        pill->retain();
        pill->setPosition(Point(x*SCALE_FACTOR,y*SCALE_FACTOR));
        addChild(pill);
        pill->setGlobalZOrder(Z_OBJ);
        auto light = Light::create(taste);
        light->retain();
        light->setPosition(Point(pill->getContentSize().width*0.5,pill->getContentSize().height*0.5));
        light->setScale(0.5);
        light->setGlobalZOrder(Z_OBJLIGHT);
        pill->addChild(light);
        pillVec.pushBack(pill);
    }
    
    // clouds
    nMaxClouds = 30;
    for (int it = 0; it < nMaxClouds; it++) {
        auto clouds = Movable::create(random(0.1, 0.4),"cloud.png");
        clouds->setScale(SCALE_FACTOR);
        clouds->setPosition(Point(random(0.0,1.0)*level->getMap()->getMapSize().width*16*SCALE_FACTOR-clouds->getContentSize().width, level->getMap()->getMapSize().height*16*SCALE_FACTOR*random(0.4,0.9)));
        clouds->setGlobalZOrder(Z_AIR);
        clouds->setScale(random(SCALE_FACTOR, SCALE_FACTOR*2));
        clouds->retain();
        addChild(clouds);
        cloudVec.pushBack(clouds);
    }
    
    // player
    player = Player::create();
    player->retain();
    this->addChild(player);
    auto *playerSpawn = level->getMap()->getObjectGroup("spawn");
    ValueVector spawnPosition = playerSpawn->getObjects();
    for (auto current : spawnPosition)
    {
        float x = current.asValueMap()["x"].asFloat()/16;
        float y = current.asValueMap()["y"].asFloat()/16;
        player->setPosition(level->tileCoordinateToPosition(Point(x,y)));
    }
    player->setGlobalZOrder(Z_PLY);
    
    // parallax
    auto levelWidthHalf = Point((level->getMap()->getMapSize().width*16*SCALE_FACTOR) * 0.5,0);
    parallaxOne = ParallaxBG::create("parallaxMount005g.png",Z_PLX1,Color3B(225,200,50),levelWidthHalf);
    this->addChild(parallaxOne);
    
    parallaxTwo = ParallaxBG::create("parallaxMount004g.png",Z_PLX2,Color3B(215,200,50),levelWidthHalf);
    this->addChild(parallaxTwo);
    
    parallaxThree = ParallaxBG::create("parallaxMount003g.png",Z_PLX3,Color3B(205,200,50),levelWidthHalf);
    this->addChild(parallaxThree);
    
    parallaxFour = ParallaxBG::create("parallaxMount002gt.png",Z_PLX4,Color3B(55,105,25),levelWidthHalf);
    this->addChild(parallaxFour);
    
    parallaxFive = ParallaxBG::create("parallaxMount001gt.png",Z_PLX5,Color3B(55,155,25),levelWidthHalf);
    this->addChild(parallaxFive);
    
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
    _shadowLayer->setGlobalZOrder(Z_SHADER);
    _shadowLayer->setAnchorPoint(Point(0.5, 0.5));
    lastPoint = Point(0,0);
    
    // Overlay
    _hud = OverlayLayer::create();
    this->addChild(_hud);
    _hud->setGlobalZOrder(Z_MENU);
    _hud->setAnchorPoint(Point(0.5, 0.5));
    
    // touch
    _touchEnabled = true;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TestSceneThree::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->schedule(schedule_selector(TestSceneThree::update), 0.01f);
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(TestSceneThree::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Device::setAccelerometerInterval(1/100);
    
    // parameters
    score = 0;
    _win = false;
    soundState = playYeah;
    cameraOff = false;
    nPills = pillVec.size();
    lastPlayerPosition = player->getPosition();
    
    pillPosition.push_back(Point(0,0));
    pillPosition.push_back(Point(0,0));
    pillDistance.push_back(9999.0f);
    pillDistance.push_back(9999.0f);
    UserDefault::getInstance()->setIntegerForKey("win", 0);
    
    this->scheduleUpdate();
    return true;
}