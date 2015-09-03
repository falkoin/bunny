#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Consumable.h"
#include "Level.h"
#include "OverlayLayer.h"
#include "ShadowLayer.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
protected:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    Player *player;
    Consumable *consumable;
    Level *level;
    Sprite *cameraTarget;
    Follow *camera;
    OverlayLayer *_hud;
    ShadowLayer* _shadowLayer;
    Sprite* parallaxOne;
    Sprite* parallaxTwo;
    
    bool _touchEnabled;
    bool _gameOver;
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
    
    void update(float dt);
    void updateCamera();
    void updatePlayerX(float dt);
    void updatePlayerY(float dt);
    void checkCollisionX();
    void checkCollisionY();
    void checkHit();
    void shader();
    virtual void gameOver();
    
    int score;
    bool _win;
    Vector<Sprite*> pillVec;
    cocos2d::Point lastPoint;

    
};

#endif // __GAME_SCENE_H__
