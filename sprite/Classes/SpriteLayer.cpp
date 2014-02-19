#include "SpriteLayer.h"

#include "Sprite.h"

SpriteLayer::SpriteLayer()
    : m_sprite(0)
{
    setTouchEnabled(true);
}

bool SpriteLayer::init()
{
    if (!CCLayer::init())
        return false;

    createSprite();

    return true;
}

void SpriteLayer::createSprite()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCSpriteBatchNode* spriteBatch = CCSpriteBatchNode::create("braid_guy.png");
    addChild(spriteBatch);

    CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("braid_guy.plist");

    CCSpriteFrame *frame = frameCache->spriteFrameByName("idle 1.png");
    m_sprite = Sprite::createWithSpriteFrame(frame);
    m_sprite->setPosition(ccp(winSize.width / 2.0, winSize.height / 2.0));
    m_sprite->nextState();

    addChild(m_sprite, 0);
}
