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
    void didSwipe(CCObject *obj);
    void didTap(CCObject *obj);
    void didDoubleTap(CCObject *obj);
    void didLongPress(CCObject *obj);
    void didPan(CCObject *obj);
    void scrollBackground(float scrollSpeed);

private:
    void createSprite();
    // scheduled Update
    void update(float dt);

    Sprite *m_sprite;
    CCParallaxNode *voidNode;
};

#endif
