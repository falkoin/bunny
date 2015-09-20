#include "ShadowLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ShadowLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
    {
        return false;
    }
    
    _lightShaderProgram = GLProgram::createWithFilenames("test.vert","shadow.fsh");
    setGLProgram(_lightShaderProgram);
    
    _lightSize = 600.0;
    _lightPosition = Point(0,0);
    _shadowColor = Vec4(0.0,0.0,0.0,0.55);

    return true;
}

void ShadowLayer::setLightPosition(Point pos)
{
    _lightPosition = pos;
}

void ShadowLayer::setLightSize(float size)
{
    _lightSize = size;
}

void ShadowLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    LayerColor::draw(renderer, transform, flags);
    _lightShaderProgram->use();
    
    GLuint position = glGetUniformLocation(_lightShaderProgram->getProgram(), "position");
    _lightShaderProgram->setUniformLocationWith2f(position, _lightPosition.x, _lightPosition.y);
    
    GLuint lightSize = glGetUniformLocation(_lightShaderProgram->getProgram(), "lightSize");
    _lightShaderProgram->setUniformLocationWith1f(lightSize, _lightSize);
    
    GLuint shadowColor = glGetUniformLocation(_lightShaderProgram->getProgram(), "shadowColor");
    _lightShaderProgram->setUniformLocationWith4f(shadowColor, _shadowColor.x, _shadowColor.y, _shadowColor.z, _shadowColor.w);
}

void ShadowLayer::setShadowColor(Vec4 color)
{
    _shadowColor = color;
}