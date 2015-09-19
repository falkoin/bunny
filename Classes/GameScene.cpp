#include "GameScene.h"
#include "Globals.h"
#include "Player.h"
#include "OverlayLayer.h"
#include "GameOverScene.h"
#include "Consumable.h"
#include "ShadowLayer.h"
#include "SimpleAudioEngine.h"
#include "Movable.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}

void GameScene::update(float dt)
{
    if (!_gameOver)
    {
        if (player->getPlayerVelocity().y < MAX_GRAVITY * SCALE_FACTOR)
        {
            player->setPlayerVelocity(Point(player->getPlayerVelocity().x, MAX_GRAVITY * SCALE_FACTOR));
        }
        else
        {
            player->setPlayerVelocity(Point(player->getPlayerVelocity().x, player->getPlayerVelocity().y + WORLD_GRAVITY * SCALE_FACTOR));
        }
    }
    checkCollisionX();
    updatePlayerX(dt);
    checkCollisionY();
    updatePlayerY(dt);
    checkHit();
    updateCamera();
    updateGameobjects();
//    log("Player Vel Y: %f", player->getPlayerVelocity().y);
    _hud->setPosition(this->convertToNodeSpace(Point(1,1)));
    _hud->updateScore(score);
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (_touchEnabled && !_gameOver)
    {
//        auto touchPosition = touch->getLocation();
        player->moveUp();
        _touchEnabled = false;
//        log("Position, %f",touchPosition.x);
    }
    if (_gameOver)
    {
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
    }
    return true;
}

void GameScene::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    float accX = acc->x;
    float meanAcc = 0;
    
    accelBuffer.push_back(accX);
    if (accelBuffer.size() > 3)
    {
        accelBuffer.erase(accelBuffer.begin());
    }
    
    for (int i = 0; i < accelBuffer.size(); i++)
    {
        meanAcc = meanAcc + accelBuffer[i];
    }
    
    accX = meanAcc/accelBuffer.size();
    
    if (accX > ACCELSENSITIVITY && !_gameOver)
    {
        player->moveRight(acc->x);
    }
    else if (accX < -ACCELSENSITIVITY && !_gameOver)
    {
        player->moveLeft(acc->x);
    }
    else
    {
        if (player->state != Player::State::Win)
            player->stop();
    }
}

void GameScene::updatePlayerX(float dt)
{
    int newPositionX = player->getPositionX()+player->getPlayerVelocity().x;
    player->setPositionX(newPositionX);
}

void GameScene::updatePlayerY(float dt)
{
    int newPositionY = player->getPositionY()+player->getPlayerVelocity().y;
    player->setPositionY(newPositionY);
}

void GameScene::checkCollisionX()
{
    // collision x
    vector<Rect> tiles;
    Rect player_rect = player->getBoundingBox();
    int nextPositionX = player_rect.getMinX() + player->getPlayerVelocity().x;
    int nextPositionY = player_rect.getMinY();
    int playerWidth  = (player_rect.getMaxX() - player_rect.getMinX()) + player->getPlayerVelocity().x;
    int playerHeight = (player_rect.getMaxY() - player_rect.getMinY());
    
    player_rect.setRect(nextPositionX, nextPositionY, playerWidth, playerHeight);
    Point tmp1;
    Point tmp2;
    Point tmp3;
    Point tmp1pos;
    Point tmp2pos;
    Point tmp3pos;
    int dic;
    if (player->getPlayerVelocity().x > 0)
    {
        tmp1pos = Point(player_rect.getMaxX(),player_rect.getMaxY()-1);
        tmp2pos = Point(player_rect.getMaxX(),player_rect.getMinY());
        tmp3pos = Point(player_rect.getMaxX(),player_rect.getMidY());
        tmp1 = level->positionToTileCoordinate(tmp1pos);
        tmp2 = level->positionToTileCoordinate(tmp2pos);
        tmp3 = level->positionToTileCoordinate(tmp3pos);
        dic = 1;
        tiles = level->getCollisionTilesX(tmp1,tmp2, tmp3, 0);
    }
    else
    {
        tmp1pos = Point(player_rect.getMinX(),player_rect.getMaxY()-1);
        tmp2pos = Point(player_rect.getMinX(),player_rect.getMinY());
        tmp3pos = Point(player_rect.getMinX(),player_rect.getMidY());
        tmp1 = level->positionToTileCoordinate(tmp1pos);
        tmp2 = level->positionToTileCoordinate(tmp2pos);
        tmp3 = level->positionToTileCoordinate(tmp3pos);
        dic = -1;
        tiles = level->getCollisionTilesX(tmp1, tmp2, tmp3, 0);
    }
    
    for (Rect tile : tiles)
    {
        if ((tile.containsPoint(tmp1pos)) || (tile.containsPoint(tmp2pos)) || (tile.containsPoint(tmp3pos)))
        {
            player->setPlayerVelocity(Point(0,player->getPlayerVelocity().y));
            if (dic == -1)
            {
                player->setPositionX(tile.getMaxX());
            }
            else if (dic == 1)
            {
                player->setPositionX(tile.getMinX()-player->getContentSize().width*SCALE_FACTOR);
            }
            break;
        }
    }
}

void GameScene::checkCollisionY()
{
    vector<Rect> tiles;
    Rect player_rect = player->getBoundingBox();
    int nextPositionX = player_rect.getMinX();
    int nextPositionY = player_rect.getMinY() + player->getPlayerVelocity().y;
    if (nextPositionY < 16*SCALE_FACTOR)
        nextPositionY = 1;
    int playerWidth   = (player_rect.getMaxX() - player_rect.getMinX());
    int playerHeight  = (player_rect.getMaxY() - player_rect.getMinY()) + player->getPlayerVelocity().y;
    
    player_rect.setRect(nextPositionX, nextPositionY, playerWidth, playerHeight);
    Point tmp1;
    Point tmp2;
    Point tmp1pos;
    Point tmp2pos;
    
    if (player->getPlayerVelocity().y >= 0)
    {
        tmp1pos = Point(player_rect.getMaxX()-1,player_rect.getMaxY());
        tmp2pos = Point(player_rect.getMinX(),player_rect.getMaxY());
        tmp1 = level->positionToTileCoordinate(tmp1pos);
        tmp2 = level->positionToTileCoordinate(tmp2pos);
        
        tiles = level->getCollisionTilesY(tmp1, tmp2, 0);
    }
    else
    {
        tmp1pos = Point(player_rect.getMaxX()-1,player_rect.getMinY());
        tmp2pos = Point(player_rect.getMinX(),player_rect.getMinY());
        tmp1 = level->positionToTileCoordinate(tmp1pos);
        tmp2 = level->positionToTileCoordinate(tmp2pos);
        tiles = level->getCollisionTilesY(tmp1, tmp2, 0);
    }
    
    for (Rect tile : tiles)
    {
        if ((tile.containsPoint(tmp1pos)) || (tile.containsPoint(tmp2pos)))
        {
            float mapheight = ((float)level->getMap()->getMapSize().height - 3) * 16 * SCALE_FACTOR;
//            log("Position Y: %f", player->getPositionY());
//            log("Mapheight: %f", mapheight);
            if (player->getPlayerVelocity().y > 0 && player->getPosition().y+player->getContentSize().height >= mapheight)
            {
                int topCollisionPosition = tile.getMinY() - (player->getContentSize().height) * SCALE_FACTOR;
                player->setPositionY(topCollisionPosition);
                _win = true;
                cameraOff = true;
                auto moveBy1 = MoveBy::create(0.1, Vec2(0,10));
                auto moveBy2 = MoveBy::create(0.1, Vec2(0,-15));
                auto moveBy3 = MoveBy::create(0.1, Vec2(0,5));
                cameraTarget->runAction(Sequence::create(moveBy1, moveBy2, moveBy3, nullptr));
                gameOver();
            }
            else if (player->getPlayerVelocity().y < 0 && !_win)
            {
                int topCollisionPosition = tile.getMaxY();
                player->setPositionY(topCollisionPosition);
                player->grounded = true;
                _touchEnabled = true;
                if (score > 0 && !_gameOver)
                {
                    gameOver();
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ouch.wav");
                    
                    cameraOff = true;
                    auto moveBy1 = MoveBy::create(0.1, Vec2(0,-10));
                    auto moveBy2 = MoveBy::create(0.1, Vec2(0,15));
                    auto moveBy3 = MoveBy::create(0.1, Vec2(0,-5));
                    cameraTarget->runAction(Sequence::create(moveBy1, moveBy2, moveBy3, nullptr));
                }
            }
            player->setPlayerVelocity(Point(player->getPlayerVelocity().x,0));
        }
    }
}

void GameScene::checkHit()
{
    if (player->state != Player::State::Dead)
    {
        for (auto *pills : pillVec)
        {
            if (pills != NULL)
            {
                Rect pillRect = pills->getBoundingBox();
                Rect playerRect = player->getBoundingBox();
                if (pillRect.intersectsRect(playerRect))
                {
                    if (pills->getTag() == 1)
                    {
                        player->moveUp();
                        ParticleSystemQuad* p = ParticleSystemQuad::create("explosionPink.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(pills->getPosition()+Point(pills->getContentSize()/2));
                        addChild(p);
                        _shadowLayer->setShadowColor(Vec4(0.86,0.17,0.87,0.55));
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bloop.wav");
                    }
                    else if (pills->getTag() == 2)
                    {
                        player->moveUpDouble();
                        ParticleSystemQuad* p = ParticleSystemQuad::create("explosionCyan.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(pills->getPosition()+Point(pills->getContentSize()/2));
                        addChild(p);
                        _shadowLayer->setShadowColor(Vec4(0.17,0.85,0.86,0.55));
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("woooh.wav");
                    }
                    else if (pills->getTag() == 3)
                    {
                        score = score*2;
                        player->moveUp();
                        ParticleSystemQuad* p = ParticleSystemQuad::create("explosionGreen.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(pills->getPosition()+Point(pills->getContentSize()/2));
                        addChild(p);
                        _shadowLayer->setShadowColor(Vec4(0.21,0.86,0.17,0.55));
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bloop.wav");
                    }
                    else
                    {
                        log("Error");
                        _shadowLayer->setShadowColor(Vec4(0.0,0.0,0.0,0.55));
                    }
                    pillVec.eraseObject(pills);
                    pills->removeFromParent();
                    score++;
                    break;
                }
            }
        }
        for (auto *collisionObject : collisionVec)
        {
            if (collisionObject != NULL)
            {
                Rect collisionObjectRect = collisionObject->getBoundingBox();
                Rect playerRect = player->getBoundingBox();
                if (collisionObjectRect.intersectsRect(playerRect))
                {
                    if (collisionObject->getDamageObjectType() == 1 && !_gameOver)
                    {
                        gameOver();
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("burn.wav");
                    }
                    if (collisionObject->getDamageObjectType() == 2 && !_gameOver)
                    {
                        gameOver();
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ouch.wav");
                    }
                    if (collisionObject->getDamageObjectType() == 3 && !_gameOver)
                    {
                        ParticleSystemQuad* p = ParticleSystemQuad::create("sawParticles.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(player->getPosition()+Point(player->getContentSize()/2));
                        addChild(p);
                        gameOver();
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ouch.wav");
                    }
                }
            }
        }
    }
}

void GameScene::updateCamera()
{
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
    auto playerPosition = player->getPosition();
    auto positionDiff = playerPosition-lastPlayerPosition;
    lastPlayerPosition = playerPosition;
    auto cameraPosition = cameraTarget->getPosition();
    int cameraSpaceFactor = 40;
    auto mapSize = level->getMap()->getMapSize();
    int mapHeight = mapSize.height*16*SCALE_FACTOR;
    int mapWidth = mapSize.width*16*SCALE_FACTOR;
    
    if (!cameraOff)
    {
        if (playerPosition.x - visibleSize.width*0.5+cameraSpaceFactor*SCALE_FACTOR <= 0)
        {
            cameraTarget->setPositionX(0+visibleSize.width*0.5);
        }
        else if ((playerPosition.x + visibleSize.width*0.5-cameraSpaceFactor*SCALE_FACTOR) >= mapWidth)
        {
            cameraTarget->setPositionX(mapWidth-visibleSize.width*0.5);
        }
        else
        {
            if (playerPosition.x-cameraPosition.x > cameraSpaceFactor * SCALE_FACTOR)
            {
                cameraTarget->setPositionX(playerPosition.x - cameraSpaceFactor * SCALE_FACTOR);
                if (parallaxOne != NULL)
                {
                    parallaxOne->setPosition(Point(parallaxOne->getPositionX()+positionDiff.x*0.9,parallaxOne->getPositionY()));
                    parallaxTwo->setPosition(Point(parallaxTwo->getPositionX()+positionDiff.x*0.8,parallaxTwo->getPositionY()));
                    parallaxThree->setPosition(Point(parallaxThree->getPositionX()+positionDiff.x*0.7,parallaxThree->getPositionY()));
                    parallaxFour->setPosition(Point(parallaxFour->getPositionX()+positionDiff.x*0.5,parallaxFour->getPositionY()));
                    
                    for (auto *clouds : cloudVec)
                    {
                        if (clouds != NULL)
                        {
                            clouds->setPositionX(clouds->getPositionX()+positionDiff.x*0.8);
                        }
                    }
                }
            }
            if (playerPosition.x-cameraPosition.x < -cameraSpaceFactor * SCALE_FACTOR)
            {
                cameraTarget->setPositionX(playerPosition.x + cameraSpaceFactor * SCALE_FACTOR);
                if (parallaxOne != NULL)
                {
                    parallaxOne->setPosition(Point(parallaxOne->getPositionX()+positionDiff.x*0.9,parallaxOne->getPositionY()));
                    parallaxTwo->setPosition(Point(parallaxTwo->getPositionX()+positionDiff.x*0.8,parallaxTwo->getPositionY()));
                    parallaxThree->setPosition(Point(parallaxThree->getPositionX()+positionDiff.x*0.7,parallaxThree->getPositionY()));
                    parallaxFour->setPosition(Point(parallaxFour->getPositionX()+positionDiff.x*0.5,parallaxFour->getPositionY()));
                    
                    for (auto *clouds : cloudVec)
                    {
                        if (clouds != NULL)
                        {
                            clouds->setPositionX(clouds->getPositionX()+positionDiff.x*0.8);
                        }
                    }
                }
            }
        }
        
        
        if (playerPosition.y - visibleSize.height*0.5+cameraSpaceFactor*SCALE_FACTOR <= 0)
        {
            cameraTarget->setPositionY(0+visibleSize.height*0.5);
        }
        else if ((playerPosition.y + visibleSize.height*0.5-cameraSpaceFactor*SCALE_FACTOR) >= mapHeight)
        {
            cameraTarget->setPositionY((mapHeight-visibleSize.height*0.5));
        }
        else
        {
            if (playerPosition.y-cameraPosition.y > cameraSpaceFactor * SCALE_FACTOR)
            {
                cameraTarget->setPositionY(playerPosition.y - cameraSpaceFactor * SCALE_FACTOR);
                if (parallaxOne != NULL)
                {
                    parallaxOne->setPosition(Point(parallaxOne->getPositionX(),parallaxOne->getPositionY()+positionDiff.y*0.7));
                    parallaxTwo->setPosition(Point(parallaxTwo->getPositionX(),parallaxTwo->getPositionY()+positionDiff.y*0.6));
                    parallaxThree->setPosition(Point(parallaxThree->getPositionX(),parallaxThree->getPositionY()+positionDiff.y*0.5));
                    parallaxFour->setPosition(Point(parallaxFour->getPositionX(),parallaxFour->getPositionY()+positionDiff.y*0.2));
                    
                    //                for (auto *clouds : cloudVec)
                    //                {
                    //                    if (clouds != NULL)
                    //                    {
                    //                        clouds->setPositionY(clouds->getPositionY()+positionDiff.x*0.5);
                    //                    }
                    //                }
                }
            }
            if (playerPosition.y-cameraPosition.y < -cameraSpaceFactor * SCALE_FACTOR)
            {
                cameraTarget->setPositionY(playerPosition.y + cameraSpaceFactor * SCALE_FACTOR);
                if (parallaxOne != NULL)
                {
                    parallaxOne->setPosition(Point(parallaxOne->getPositionX(),parallaxOne->getPositionY()+positionDiff.y*0.7));
                    parallaxTwo->setPosition(Point(parallaxTwo->getPositionX(),parallaxTwo->getPositionY()+positionDiff.y*0.6));
                    parallaxThree->setPosition(Point(parallaxThree->getPositionX(),parallaxThree->getPositionY()+positionDiff.y*0.5));
                    parallaxFour->setPosition(Point(parallaxFour->getPositionX(),parallaxFour->getPositionY()+positionDiff.y*0.2));
                    
                    //                for (auto *clouds : cloudVec)
                    //                {
                    //                    if (clouds != NULL)
                    //                    {
                    //                        clouds->setPositionY(clouds->getPositionY()+positionDiff.x*0.5);
                    //                    }
                    //                }
                }
            }
        }
    }
}

void GameScene::gameOver()
{
    if (!_gameOver)
    {
        if (!_win)
        {
            _hud->drawEndMessage();
            player->removeFromParent();
            ParticleSystemQuad* p = ParticleSystemQuad::create("explosionPlayer.plist");
            p->setGlobalZOrder(1010);
            p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
            p->setPosition(player->getPosition()+Point(player->getContentSize()/2));
            addChild(p);
            _shadowLayer->setShadowColor(Vec4(1.0,0.0,0.0,0.55));
            
        }
        else if (_win)
        {
            _hud->drawWinMessage();
            player->win();
        }
        else
        {
            log("Error end message");
        }
        _gameOver = true;
        player->setPlayerVelocity(Point(0,0));
        
    }
}

void GameScene::updateGameobjects()
{
    // shader
    Point playerInWorld = this->convertToWorldSpace(Point(player->getPositionX()+player->getContentSize().width/2*SCALE_FACTOR,player->getPositionY()+player->getContentSize().height/2*SCALE_FACTOR));
    if (abs(playerInWorld.x - lastPoint.x) > 2 * SCALE_FACTOR || abs(playerInWorld.y - lastPoint.y) > 2 * SCALE_FACTOR)
    {
        lastPoint = lastPoint.lerp(playerInWorld, 0.01);
    }
    _shadowLayer->setLightPosition(lastPoint);
    _shadowLayer->setPosition(this->convertToNodeSpace(Point(0,0)));
    
    for (auto *clouds : cloudVec)
    {
        if (clouds != NULL)
        {
            clouds->setPositionX(clouds->getPositionX()+clouds->getSpeed());
            if (clouds->getPositionX() > level->getMap()->getMapSize().width*16*SCALE_FACTOR)
            {
                cloudVec.eraseObject(clouds);
                clouds->removeFromParent();
            }
        }
    }
    
    // clouds
    if (cloudVec.size() < nMaxClouds)
    {
        auto clouds = Movable::create(random(0.1, 0.4),"cloud.png");
        clouds->setPosition(Point(0-clouds->getContentSize().width, level->getMap()->getMapSize().height*16*SCALE_FACTOR*random(0.2,0.9)));
        clouds->setScale(random(SCALE_FACTOR, SCALE_FACTOR*2));
        clouds->setGlobalZOrder(2);
        clouds->retain();
        addChild(clouds);
        cloudVec.pushBack(clouds);
    }

    // animations
    player->animate();
    
    // sounds
    
    if (pillVec.size() <= round(nPills*0.2) && !awesomePlayed)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("awesome.wav");
        _hud->shouOut((std::string)"Awesome!!!");
        awesomePlayed = true;
    }
    
//    log("n clouds = %i", cloudVec.size());
    
    // falling objects
    
    if (fallingVec.size() < nMaxFallingObjects)
    {
        
    }
}