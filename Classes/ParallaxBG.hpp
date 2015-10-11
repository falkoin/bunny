//
//  ParallaxBG.hpp
//  bunny
//
//  Created by Falko Döhring on 10.10.15.
//
//

#ifndef ParallaxBG_hpp
#define ParallaxBG_hpp

#include "cocos2d.h"

class ParallaxBG : public cocos2d::Sprite
{
public:
    ParallaxBG();
    virtual ~ParallaxBG();
    static ParallaxBG* create(std::string filename, int zorder, cocos2d::Color3B color, cocos2d::Point pos);
    void setShader(float val);
    
private:
    cocos2d::GLProgramState* _glprogramstate;
    void initOptions();
};


#endif /* ParallaxBG_hpp */
