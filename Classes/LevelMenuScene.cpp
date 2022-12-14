#include "LevelMenuScene.h"
#include "TestScene.h"
#include "TestSceneTwo.h"
#include "TestSceneThree.h"
#include "TestSceneFour.h"
#include "TestSceneFive.h"
#include "MainMenuScene.h"
#include "Globals.h"
#include "CocosGUI.h"
#include "cocos-ext.h"


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
    this->addChild(backgroundSprite,1);
    
    auto titleLabel = Sprite::create("levels.png");
    titleLabel->setScale(SCALE_FACTOR/2.0f);
    titleLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height *9.2/10 + origin.y));
    this->addChild(titleLabel,3);
    
    auto backItem = MenuItemImage::create("buttonBack.png","buttonBackPressed.png",CC_CALLBACK_1(LevelMenuScene::goBack, this));
    backItem->setScale(SCALE_FACTOR/5.0f);
    backItem->setPosition(Point(origin.x+visibleSize.width*1/10, visibleSize.height * 9.2/10 + origin.y));
    auto menuBack = Menu::create(backItem, NULL);
    menuBack->setPosition(Point::ZERO);
    
    this->addChild(menuBack,3);
    
    Size scollFrameSize = Size(visibleSize.width, visibleSize.height);
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(scollFrameSize);
    scrollView->setPosition(Point(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(false);
    scrollView->setTouchEnabled(true);
    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height*2);
    scrollView->setInnerContainerSize(containerSize);
    
    this->addChild(scrollView,2);
    
    float hsPos = 0.5;
    
    auto playItem = MenuItemImage::create("lvl01.png","lvl01pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelOne, this));
    playItem->setScale(SCALE_FACTOR/3.0f);
    playItem->setPosition(Point( containerSize.width / 2 + origin.x, containerSize.height * 3.5/4 + origin.y));
    
    auto lvlOneLabel = setSublabelHS("Level001HS");
    lvlOneLabel->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 3.4/4 + origin.y));
    scrollView->addChild(lvlOneLabel);
    auto lvlOneLabelT = setSublabelT("Level001T");
    lvlOneLabelT->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 3.35/4 + origin.y));
    scrollView->addChild(lvlOneLabelT);
    
    auto playItem2 = MenuItemImage::create("lvl02.png","lvl02pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelTwo, this));
    playItem2->setScale(SCALE_FACTOR/3.0f);
    playItem2->setPosition(Point( containerSize.width / 2 + origin.x, containerSize.height * 3.2/4 + origin.y));
    
    auto lvlTwoLabel = setSublabelHS("Level002HS");
    lvlTwoLabel->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 3.1/4 + origin.y));
    scrollView->addChild(lvlTwoLabel);
    auto lvlTwoLabelT = setSublabelT("Level002T");
    lvlTwoLabelT->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 3.05/4 + origin.y));
    scrollView->addChild(lvlTwoLabelT);
    
    auto playItem3 = MenuItemImage::create("lvl03.png","lvl03pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelThree, this));
    playItem3->setScale(SCALE_FACTOR/3.0f);
    playItem3->setPosition(Point( containerSize.width / 2 + origin.x, containerSize.height * 2.9/4 + origin.y));
    
    auto lvlThreeLabel = setSublabelHS("Level003HS");
    lvlThreeLabel->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.8/4 + origin.y));
    scrollView->addChild(lvlThreeLabel);
    auto lvlThreeLabelT = setSublabelT("Level003T");
    lvlThreeLabelT->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.75/4 + origin.y));
    scrollView->addChild(lvlThreeLabelT);
    
    auto playItem4 = MenuItemImage::create("lvl04.png","lvl04pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelFour, this));
    playItem4->setScale(SCALE_FACTOR/3.0f);
    playItem4->setPosition(Point( containerSize.width / 2 + origin.x, containerSize.height * 2.6/4 + origin.y));
    
    auto lvlFourLabel = setSublabelHS("Level004HS");
    lvlFourLabel->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.5/4 + origin.y));
    scrollView->addChild(lvlFourLabel);
    auto lvlFourLabelT = setSublabelT("Level004T");
    lvlFourLabelT->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.45/4 + origin.y));
    scrollView->addChild(lvlFourLabelT);
    
    auto playItem5 = MenuItemImage::create("lvl05.png","lvl05pressed.png",CC_CALLBACK_1(LevelMenuScene::goToLevelFive, this));
    playItem5->setScale(SCALE_FACTOR/3.0f);
    playItem5->setPosition(Point( containerSize.width / 2 + origin.x, containerSize.height * 2.3/4 + origin.y));
    
    auto lvlFiveLabel = setSublabelHS("Level005HS");
    lvlFiveLabel->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.2/4 + origin.y));
    scrollView->addChild(lvlFiveLabel);
    auto lvlFiveLabelT = setSublabelT("Level005T");
    lvlFiveLabelT->setPosition(Point( containerSize.width * hsPos + origin.x, containerSize.height * 2.15/4 + origin.y));
    scrollView->addChild(lvlFiveLabelT);

    auto menu = Menu::create(playItem, playItem2, playItem3, playItem4, playItem5,  NULL);
    menu->setPosition(Point::ZERO);
    
    scrollView->addChild(menu);

    return true;
}

void LevelMenuScene::goToLevelOne(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 1);
    auto scene = TestScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
    
}

void LevelMenuScene::goToLevelTwo(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 2);
    auto scene = TestSceneTwo::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}

void LevelMenuScene::goToLevelThree(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 3);
    auto scene = TestSceneThree::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}

void LevelMenuScene::goToLevelFour(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 4);
    auto scene = TestSceneFour::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}

void LevelMenuScene::goToLevelFive(Ref *sender)
{
    UserDefault::getInstance()->setIntegerForKey("currentLevel", 5);
    auto scene = TestSceneFive::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}

void LevelMenuScene::goBack(Ref *sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(LEVEL_TRANSITION_TIME, scene));
}

Label* LevelMenuScene::setSublabelHS(const char *labelText)
{
    auto lvlOneHC = UserDefault::getInstance()->getIntegerForKey(labelText);
    char lvlStr[20];
    sprintf(lvlStr, "Highscore: %i",lvlOneHC);
//    auto lvlOneLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","",CCTextAlignment::CENTER);
    auto lvlOneLabel = cocos2d::Label::createWithTTF("", "rainyhearts.ttf", 32);
    lvlOneLabel->setColor(cocos2d::Color3B(255, 255, 255));
    lvlOneLabel->setAnchorPoint(Point(0.5,0.5));
//    lvlOneLabel->setScale(SCALE_FACTOR/6);
    lvlOneLabel->getTexture()->setAliasTexParameters();
    lvlOneLabel->setGlobalZOrder(9999);
    lvlOneLabel->Label::setString(lvlStr);
    return lvlOneLabel;
}

Label* LevelMenuScene::setSublabelT(const char *labelText)
{
    auto lvlOneHC = UserDefault::getInstance()->getFloatForKey(labelText);
    char lvlStr[20];
    sprintf(lvlStr, "Time: %5.2f",lvlOneHC);
//    auto lvlOneLabel = cocos2d::Label::createWithBMFont("CartonSixBMP.fnt","",CCTextAlignment::CENTER);
    auto lvlOneLabel = cocos2d::Label::createWithTTF("", "rainyhearts.ttf", 32);
    lvlOneLabel->setColor(cocos2d::Color3B(255, 255, 255));
    lvlOneLabel->setAnchorPoint(Point(0.5,0.5));
//    lvlOneLabel->setScale(SCALE_FACTOR/6);
    lvlOneLabel->getTexture()->setAliasTexParameters();
    lvlOneLabel->setGlobalZOrder(9999);
    lvlOneLabel->Label::setString(lvlStr);
    return lvlOneLabel;
}