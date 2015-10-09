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
#include "TestSceneTwo.h"
#include "TestSceneThree.h"
#include "TestSceneFour.h"
#include "TestSceneFive.h"
#include "Globals.h"
#include "LevelMenuScene.h"


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
    auto gameoverSprite = Sprite::create("labelGameover.png");
    gameoverSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 8.5/10 + origin.y));
    this->addChild(gameoverSprite,2);

    auto playItem = MenuItemImage::create("buttonRetry.png","buttonRetryPressed.png",CC_CALLBACK_1(GameOverScene::gotToGameScene, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( visibleSize.width * 0.5 + origin.x, visibleSize.height / 2 + origin.y));
    
    auto playItem2 = MenuItemImage::create("buttonBack.png","buttonBackPressed.png",CC_CALLBACK_1(GameOverScene::gotToMenuScene, this));
    playItem2->setScale(SCALE_FACTOR/6.0f);
    playItem2->setPosition(Point(origin.x+visibleSize.width*1/10, visibleSize.height * 9.2/10 + origin.y));
    
    auto menu = Menu::create(playItem,playItem2,NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);
    
    _scoreLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","");
    _scoreLabel->setColor(cocos2d::Color3B(255, 255, 255));
    _scoreLabel->setAnchorPoint(Point(0.0,0.0));
    _scoreLabel->setScale(SCALE_FACTOR*0.5);
    _scoreLabel->getTexture()->setAliasTexParameters();
    _scoreLabel->setGlobalZOrder(9999);
    _scoreLabel->retain();
    addChild(_scoreLabel);
    
    auto _timeLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","");
    _timeLabel->setColor(cocos2d::Color3B(255, 255, 255));
    _timeLabel->setAnchorPoint(Point(0.0,0.0));
    _timeLabel->setScale(SCALE_FACTOR*0.5);
    _timeLabel->getTexture()->setAliasTexParameters();
    _timeLabel->setGlobalZOrder(9999);
    _timeLabel->retain();
    addChild(_timeLabel);
    
    int currentLevel = UserDefault::getInstance()->getIntegerForKey("currentLevel");
    int score = UserDefault::getInstance()->getIntegerForKey("currentScore");
    
    char levelHS[10];
    sprintf(levelHS, "Level%03dHS",currentLevel);
    int currentHS = UserDefault::getInstance()->getIntegerForKey(levelHS);
    int win = UserDefault::getInstance()->getIntegerForKey("win");
    if (score > currentHS) {
        UserDefault::getInstance()->setIntegerForKey(levelHS,score);
        _scoreLabel->Label::setString("New Highscore: "+std::to_string(score));
        _scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.25f)));
        _scoreLabel->setColor(Color3B(255,0,0));
    }
    else
    {
        _scoreLabel->Label::setString("Score: "+std::to_string(score));
        _scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.25f)));
    }
    
//    _scoreLabel->Label::setString("Score: "+std::to_string(score));
//    _scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.25f)));
    
    float time = UserDefault::getInstance()->getFloatForKey("currentTime");
    
    char levelT[9];
    sprintf(levelT, "Level%03dT",currentLevel);
    char timeNow[7];
    sprintf(timeNow, "%5.2f",time);
    
    int currentT = UserDefault::getInstance()->getIntegerForKey(levelT);
    if (time < currentT && win == 1) {
        UserDefault::getInstance()->setFloatForKey(levelT,time);
        _timeLabel->Label::setString("New Record Time: "+(std::string)timeNow);
        _timeLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.15f)));
        _timeLabel->setColor(Color3B(255,0,0));
        _timeLabel->setScale(SCALE_FACTOR/4);
    }
    else
    {
        _timeLabel->Label::setString("Time: "+(std::string)timeNow);
        _timeLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.15f)));
    }
    
//    _scoreLabel->Label::setString("Score: "+std::to_string(score));
//    _scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width*0.5f-_scoreLabel->getContentSize().width*0.5f-25,origin.y + origin.y+visibleSize.height*(0.25f)));

    
    return true;
}

void GameOverScene::gotToGameScene(Ref *sender)
{
    int currentLevel = UserDefault::getInstance()->getIntegerForKey("currentLevel");
    auto scene  = TestScene::createScene();
    if (currentLevel == 1)
    {
        scene = TestScene::createScene();
    }
    else if (currentLevel == 2)
    {
        scene = TestSceneTwo::createScene();
    }
    else if (currentLevel == 3)
    {
        scene = TestSceneThree::createScene();
    }
    else if (currentLevel == 4)
    {
        scene = TestSceneFour::createScene();
    }
    else if (currentLevel == 5)
    {
        scene = TestSceneFive::createScene();
    }
    else
    {
        scene = MainMenuScene::createScene();
        log("Level Change Error");
    }
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

void GameOverScene::gotToMenuScene(Ref *sender)
{
    auto scene = LevelMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene));
}
