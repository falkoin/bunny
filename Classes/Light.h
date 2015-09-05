//
//  Light.h
//  platPro
//
//  Created by Falko Döhring on 23.05.15.
//
//

#ifndef __platPro__Light__
#define __platPro__Light__

#include "cocos2d.h"

class Light : public cocos2d::Sprite
{
public:
    Light();
    virtual ~Light();
    static Light* create(int taste);
private:
    void initOptions();
    cocos2d::__String lightString;
};

#endif /* defined(__platPro__Light__) */