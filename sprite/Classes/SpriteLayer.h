#ifndef SPRITELAYER_H
#define SPRITELAYER_H

#include <cocos2d.h>

USING_NS_CC;

class Sprite;

class SpriteLayer : public CCLayer
{
public:
    SpriteLayer();

    CREATE_FUNC(SpriteLayer);

    virtual bool init();

private:
    void createSprite();

    Sprite *m_sprite;
};

#endif
