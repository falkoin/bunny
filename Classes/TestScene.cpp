//
//  TestScene.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "TestScene.h"
#include "GameScene.h"
#include "Level.h"
#include "Globals.h"
#include "OverlayLayer.h"
#include "MainMenuScene.h"
#include "Light.h"
#include "DamageObject.hpp"

USING_NS_CC;

Scene* TestScene::createScene()
{
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
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
    level->loadMap("testLevel.tmx",this);
    level->getMap()->setScale(SCALE_FACTOR);
    this->addChild(level->getMap(),-1);
    auto bg = level->getMap()->getLayer("background");
//    auto bg = Sprite::create("bgTest.png");
//    bg->setAnchorPoint(Point(0,0));
//    bg->setPosition(Point(0,0));
//    bg->setScale(SCALE_FACTOR);
//    addChild(bg);
    bg->setGlobalZOrder(2);
    
    auto walls = level->getMap()->getLayer("walls");
    walls->setGlobalZOrder(7);
    auto wallShadow = level->getMap()->getLayer("wallShadow");
    wallShadow->setGlobalZOrder(7);
//    auto mg = level->getMap()->getLayer("midground");
//    mg->setGlobalZOrder(6);
    

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
        int dmgObjType = current.asValueMap()["dmgObj"].asInt();
        if (taste != 0)
        {
            pill = Consumable::create(taste);
            pill->setTag(taste);
            pill->retain();
            pill->setPosition(Point(x*SCALE_FACTOR,y*SCALE_FACTOR));
            addChild(pill);
            auto light = Light::create(taste);
            light->retain();
            light->setPosition(Point(pill->getContentSize().width*0.5,pill->getContentSize().height*0.5));
            light->setScale(0.5);
            light->setGlobalZOrder(15);
            pill->addChild(light);
            pill->setGlobalZOrder(16);
            pillVec.pushBack(pill);
        }
        if (dmgObjType != 0)
        {
            auto dmgObj = DamageObject::create(dmgObjType);
            dmgObj->retain();
            dmgObj->setPosition(Point(x*SCALE_FACTOR,y*SCALE_FACTOR));
            dmgObj->setGlobalZOrder(14);
            
//            dmgObj->setColor(Color3B(255,100,180));
            collisionVec.pushBack(dmgObj);
            addChild(dmgObj);
            if (dmgObjType == 2)
            {
                auto light = Light::create(9);
                light->retain();
                light->setPosition(Point(dmgObj->getContentSize().width*0.5,dmgObj->getContentSize().height*0.5));
                light->setScale(0.5);
                light->setGlobalZOrder(13);
                dmgObj->addChild(light);
            }
            if (dmgObjType == 3)
            {
                dmgObj->setGlobalZOrder(2);
            }
        }
        
    }
    
    // parallax
    parallaxOne = Sprite::create("parallaxHill001.png");
    parallaxOne->setColor(Color3B(255,100,180));
    parallaxOne->setGlobalZOrder(3);
    parallaxOne->setScale(SCALE_FACTOR);
    parallaxOne->getTexture()->setAliasTexParameters();
    parallaxOne->setPosition(Point(visibleSize.width*0.5+origin.x,visibleSize.height*0.5+origin.y));
    parallaxOne->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxOne);
    
    parallaxTwo = Sprite::create("parallaxHill002.png");
    parallaxTwo->setColor(Color3B(255,100,180));
    parallaxTwo->setGlobalZOrder(4);
    parallaxTwo->setScale(SCALE_FACTOR);
    parallaxTwo->getTexture()->setAliasTexParameters();
    parallaxTwo->setPosition(Point(visibleSize.width*0.5+origin.x,visibleSize.height*0.5+origin.y));
    parallaxTwo->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxTwo);
    
    parallaxThree = Sprite::create("parallaxHill003.png");
    parallaxThree->setColor(Color3B(255,100,180));
    parallaxThree->setGlobalZOrder(5);
    parallaxThree->setScale(SCALE_FACTOR);
    parallaxThree->getTexture()->setAliasTexParameters();
    parallaxThree->setPosition(Point(visibleSize.width*0.5+origin.x,visibleSize.height*0.5+origin.y));
    parallaxThree->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxThree);
    
    parallaxFour = Sprite::create("parallaxFront001.png");
    parallaxFour->setColor(Color3B(255,100,180));
    parallaxFour->setGlobalZOrder(6);
    parallaxFour->setScale(SCALE_FACTOR);
    parallaxFour->getTexture()->setAliasTexParameters();
    parallaxFour->setPosition(Point(visibleSize.width*0.5+origin.x,visibleSize.height*0.5+origin.y));
    parallaxFour->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(parallaxFour);
    
    // clouds
    nMaxClouds = 20;
    for (int it = 0; it < nMaxClouds; it++) {
        auto clouds = Movable::create(random(0.1, 0.4),"cloud.png");
        clouds->setScale(SCALE_FACTOR);
        clouds->setPosition(Point(random(0.0,1.0)*level->getMap()->getMapSize().width*16*SCALE_FACTOR-clouds->getContentSize().width, level->getMap()->getMapSize().height*16*SCALE_FACTOR*random(0.4,0.9)));
        clouds->setGlobalZOrder(3);
        clouds->setScale(random(SCALE_FACTOR, SCALE_FACTOR*2));
        clouds->retain();
        addChild(clouds);
        cloudVec.pushBack(clouds);
    }

    
    // player
    player = Player::create();
    player->retain();
    this->addChild(player);
    player->setPosition(level->tileCoordinateToPosition(Point(7,1)));
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
    touchListener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->schedule(schedule_selector(TestScene::update), 0.01f);
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(TestScene::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Device::setAccelerometerInterval(1/100);
    
    // parameters
    score = 0;
    _win = false;
    
    
    lastPlayerFallingPosition = player->getPositionY();
    playerFallDistance = 0.0f;
    awesomePlayed = false;
    nPills = pillVec.size();
    cameraOff = false;
    
    this->scheduleUpdate();
    return true;
}