#include "GameScene.h"
#include "Globals.h"
#include "Player.h"
#include "OverlayLayer.h"
#include "GameOverScene.h"
#include "Consumable.h"

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
        player->setPlayerVelocity(Point(player->getPlayerVelocity().x, player->getPlayerVelocity().y + WORLD_GRAVITY * SCALE_FACTOR));
    }
    checkCollisionX();
    updatePlayerX(dt);
    checkCollisionY();
    updatePlayerY(dt);
    updateCamera();
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
//    float accY = acc->y;
//    float accZ = acc->z;
//    log("Accel Y: %f", accX);
//    log("Velocity X: %f", player->getPlayerVelocity().x);
    if (accX > ACCELSENSITIVITY && !_gameOver)
    {
        player->moveRight();
    }
    else if (accX < -ACCELSENSITIVITY && !_gameOver)
    {
        player->moveLeft();
    }
    else
    {
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
    
    checkHit();
}

void GameScene::checkCollisionY()
{
    vector<Rect> tiles;
    Rect player_rect = player->getBoundingBox();
    int nextPositionX = player_rect.getMinX();
    int nextPositionY = player_rect.getMinY() + player->getPlayerVelocity().y;
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
            if (player->getPlayerVelocity().y > 0)
            {
                int topCollisionPosition = tile.getMinY() - (player->getContentSize().height) * SCALE_FACTOR;
                player->setPositionY(topCollisionPosition);
                _win = true;
                gameOver();
            }
            else if (player->getPlayerVelocity().y < 0 && !_win)
            {
                int topCollisionPosition = tile.getMaxY();
                player->setPositionY(topCollisionPosition);
                player->grounded = true;
                _touchEnabled = true;
                if (score > 0)
                {
                    gameOver();
                }
            }
            player->setPlayerVelocity(Point(player->getPlayerVelocity().x,0));
        }
    }
    checkHit();
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


//                    std::chrono::milliseconds duration( 30 );
//                    std::this_thread::sleep_for( duration );
                    if (pills->getTag() == 1)
                    {
                        player->moveUp();
                        ParticleSystemQuad* p = ParticleSystemQuad::create("explosionPink.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(pills->getPosition()+Point(pills->getContentSize()/2));
                        addChild(p);
                    }
                    else if (pills->getTag() == 2)
                    {
                        player->moveUpDouble();
                        ParticleSystemQuad* p = ParticleSystemQuad::create("explosionCyan.plist");
                        p->setGlobalZOrder(1010);
                        p->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
                        p->setPosition(pills->getPosition()+Point(pills->getContentSize()/2));
                        addChild(p);
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
                    }
                    else
                    {
                        log("Error");
                    }
                    pillVec.eraseObject(pills);
                    pills->removeFromParent();
                    score++;

                }
            }
        }
    }
}

void GameScene::updateCamera()
{
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();
//    auto test = convertToNodeSpace(origin);
    auto playerPosition = player->getPosition();
    auto cameraPosition = cameraTarget->getPosition();
    int cameraSpaceFactor = 40;
    auto mapSize = level->getMap()->getMapSize();
    int mapHeight = mapSize.height*16*SCALE_FACTOR;
    
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
            cameraTarget->setPositionY((int)playerPosition.y - cameraSpaceFactor * SCALE_FACTOR);
        }
        else if (playerPosition.y-cameraPosition.y < -cameraSpaceFactor * SCALE_FACTOR)
        {
            cameraTarget->setPositionY((int)playerPosition.y + cameraSpaceFactor * SCALE_FACTOR);
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
        }
        else if (_win)
        {
            _hud->drawWinMessage();
        }
        else
        {
            log("Error end message");
        }
        _gameOver = true;
        player->setPlayerVelocity(Point(0,0));
        
    }
}