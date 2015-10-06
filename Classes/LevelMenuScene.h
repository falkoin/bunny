#ifndef __LEVEL_MENU_SCENE_H__
#define __LEVEL_MENU_SCENE_H__

#include "cocos2d.h"

class LevelMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelMenuScene);
    
private:
    void goToLevelOne(Ref *sender);
    void goToLevelTwo(Ref *sender);
    void goToLevelThree(Ref *sender);
    void goToLevelFour(Ref *sender);
    void goToLevelFive(Ref *sender);
    void goBack(Ref *sender);
};

#endif // __LEVEL_MENU_SCENE_H__
