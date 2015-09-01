#ifndef __SHADOWLAYER_H__
#define __SHADOWLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ShadowLayer : public LayerColor {

public:
    virtual bool init();
    CREATE_FUNC(ShadowLayer);
    
    void setLightPosition(Point pos);
    void setLightSize(float size);
    void setShadowColor(Vec4 color);
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
private:
    GLProgram* _lightShaderProgram;
    Point _lightPosition;
    float _lightSize;
    Vec4 _shadowColor;
    int _program;
    
};

#endif
