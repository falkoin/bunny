//
//  ParallaxBG.cpp
//  bunny
//
//  Created by Falko Döhring on 10.10.15.
//
//

#include "ParallaxBG.hpp"
#include "Globals.h"

USING_NS_CC;

ParallaxBG::ParallaxBG()
{
}

ParallaxBG::~ParallaxBG()
{
}

ParallaxBG* ParallaxBG::create(std::string filename, int zorder, cocos2d::Color3B color, Point pos)
{
    ParallaxBG* pSprite = new ParallaxBG();
    if (pSprite->initWithFile(filename))
    {
        pSprite->initOptions();
        pSprite->autorelease();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setGlobalZOrder(zorder);
        pSprite->setColor(color);
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setAnchorPoint(Vec2(0.5,0));
        pSprite->setPosition(pos);
        pSprite->setFlippedX(false);
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void ParallaxBG::initOptions()
{
//    auto fileUtiles = FileUtils::getInstance();
//    auto fragmentFullPath = fileUtiles->fullPathForFilename("wind.fsh");
//    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
//    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
//    
//    
//    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
//    _glprogramstate->retain();
//    _glprogramstate->setUniformFloat("u_wind", 0.5f);
//    this->setGLProgramState(_glprogramstate);
}

void ParallaxBG::setShader(float val)
{
//    _glprogramstate->setUniformFloat("u_wind", val);
}
