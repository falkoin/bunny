//
//  TestSceneThree.h
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#ifndef __bunny__TestSceneThree__
#define __bunny__TestSceneThree__

#include "cocos2d.h"
#include "GameScene.h"

class TestSceneThree : public GameScene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestSceneThree);
protected:
    cocos2d::Sprite* pill;
};

#endif /* defined(__bunny__TestSceneThree__) */
