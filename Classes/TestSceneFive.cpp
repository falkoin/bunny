//
//  TestSceneFive.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "TestSceneFive.h"
#include "GameScene.h"
#include "Level.h"
#include "Globals.h"
#include "OverlayLayer.h"
#include "MainMenuScene.h"
#include "Light.h"

USING_NS_CC;

Scene* TestSceneFive::createScene()
{
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestSceneFive::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSceneFive::init()
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
    level->loadMap("testLevel5.tmx",this);
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
        if (trigger != 0 && taste != 4)
            triggered = false;
        else
            triggered = true;
        int dmgObjType = current.asValueMap()["dmgObj"].asInt();
        if (taste != 0)
        {
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
        if (dmgObjType != 0)
        {
            auto dmgObj = DamageObject::create(dmgObjType);
            dmgObj->retain();
            dmgObj->setPosition(Point(x*SCALE_FACTOR,y*SCALE_FACTOR));
            dmgObj->setGlobalZOrder(Z_OBJ);
            
            //            dmgObj->setColor(Color3B(255,100,180));
            collisionVec.pushBack(dmgObj);
            addChild(dmgObj);
            if (dmgObjType == 2)
            {
                auto light = Light::create(9);
                light->retain();
                light->setPosition(Point(dmgObj->getContentSize().width*0.5,dmgObj->getContentSize().height*0.5));
                light->setScale(0.5);
                light->setGlobalZOrder(Z_OBJLIGHT);
                dmgObj->addChild(light);
            }
            if (dmgObjType == 3)
            {
                dmgObj->setGlobalZOrder(Z_WALLS-1);
            }
        }
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

    // parallax
    parallaxOne = Sprite::create("parallaxHill001g.png");
    parallaxOne->setColor(Color3B(225,100,00));
    parallaxOne->setGlobalZOrder(Z_PLX1);
    parallaxOne->setScale(SCALE_FACTOR);
    parallaxOne->getTexture()->setAliasTexParameters();
    parallaxOne->setAnchorPoint(Point(0.5, 0));
    parallaxOne->setPosition(Point(32*16*SCALE_FACTOR-parallaxOne->getContentSize().width*0.5*SCALE_FACTOR,0));
    this->addChild(parallaxOne);
    
    parallaxTwo = Sprite::create("parallaxHill002g.png");
    parallaxTwo->setColor(Color3B(215,100,0));
    parallaxTwo->setGlobalZOrder(Z_PLX2);
    parallaxTwo->setScale(SCALE_FACTOR);
    parallaxTwo->getTexture()->setAliasTexParameters();
    parallaxTwo->setAnchorPoint(Point(0.5, 0));
    parallaxTwo->setPosition(Point(32*16*SCALE_FACTOR-parallaxTwo->getContentSize().width*0.5*SCALE_FACTOR,0));
    this->addChild(parallaxTwo);
    
    parallaxThree = Sprite::create("parallaxHill003g.png");
    parallaxThree->setColor(Color3B(205,100,0));
    parallaxThree->setGlobalZOrder(Z_PLX3);
    parallaxThree->setScale(SCALE_FACTOR);
    parallaxThree->getTexture()->setAliasTexParameters();
    parallaxThree->setAnchorPoint(Point(0.5, 0));
    parallaxThree->setPosition(Point(32*16*SCALE_FACTOR-parallaxThree->getContentSize().width*0.5*SCALE_FACTOR,0));
    this->addChild(parallaxThree);
    
    parallaxFour = Sprite::create("trees_2bw.png");
    parallaxFour->setColor(Color3B(55,75,52));
    parallaxFour->setGlobalZOrder(Z_PLX4);
    parallaxFour->setScale(SCALE_FACTOR);
    parallaxFour->getTexture()->setAliasTexParameters();
    parallaxFour->setPosition(Point(32*16*SCALE_FACTOR-parallaxFour->getContentSize().width*0.5*SCALE_FACTOR,0));
    parallaxFour->setAnchorPoint(Point(0.5, 0));
    this->addChild(parallaxFour);
    
    parallaxFive = Sprite::create("trees_bw.png");
    parallaxFive->setColor(Color3B(35,155,40));
    parallaxFive->setGlobalZOrder(Z_PLX5);
    parallaxFive->setScale(SCALE_FACTOR);
    parallaxFive->getTexture()->setAliasTexParameters();
    parallaxFive->setPosition(Point(64*16*SCALE_FACTOR-parallaxFive->getContentSize().width*0.5*SCALE_FACTOR,0));
    parallaxFive->setAnchorPoint(Point(0.5, 0));
    this->addChild(parallaxFive);
    
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
    touchListener->onTouchBegan = CC_CALLBACK_2(TestSceneFive::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->schedule(schedule_selector(TestSceneFive::update), 0.01f);
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(TestSceneFive::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Device::setAccelerometerInterval(1/100);
    
    // parameters
    score = 0;
    _win = false;
    soundState = playYeah;
    cameraOff = false;
    nPills = pillVec.size();
    pillPosition.push_back(Point(0,0));
    pillPosition.push_back(Point(0,0));
    pillDistance.push_back(9999.0f);
    pillDistance.push_back(9999.0f);
    this->scheduleUpdate();
    return true;
}