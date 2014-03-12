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
    void updateBgPosition(CCSprite* pBg, int updateSteps, float dt);
    void moveBg(int steps);
    void updateBg(int vel);
    void moveSprite(int steps);
    void setVel(int vel) { m_vel = vel; }

private:
    void createSprite();
    // scheduled Update
    void update(float dt);

    Sprite *m_sprite;
    CCParallaxNode *node;
    std::map<int, CCSprite*> m_bgMap;
    float m_bgWidth;
    int m_vel;
};

#endif
