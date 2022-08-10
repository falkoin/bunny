//
//  Player.h
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#ifndef __bunny__Enemy__
#define __bunny__Enemy__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    Enemy();
    virtual ~Enemy();
    static Enemy* create();
    
private:
    void initOptions();
};


#endif /* defined(__bunny__Player__) */
