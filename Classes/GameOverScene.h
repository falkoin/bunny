//
//  GameOverScene.h
//  bunny
//
//  Created by Falko Döhring on 29.08.15.
//
//

#ifndef __bunny__GameOverScene__
#define __bunny__GameOverScene__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
private:
    void gotToGameScene(Ref *sender);
    void gotToMenuScene(Ref *sender);
};

#endif /* defined(__bunny__GameOverScene__) */
