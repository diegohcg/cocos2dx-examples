#include "MainLayer.h"

bool MainLayer::init()
{
    if (!CCLayer::init())
        return false;

    createSprite();

    return true;
}

void MainLayer::createSprite()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSpriteBatchNode* spriteBatch = CCSpriteBatchNode::create("braid_guy.png");
    addChild(spriteBatch);

    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("braid_guy.plist");

    CCSprite *sprite = CCSprite::createWithSpriteFrameName("running 1.png");
    sprite->setPosition(ccp(s.width / 2.0, s.height / 2.0));

    CCArray* runningFrames = CCArray::create();
    CCSpriteFrame *frame;
    char tmp[50];
    for (int i = 0; i < 27; i++) {
        sprintf(tmp, "running %d.png", i + 1);
        frame = cache->spriteFrameByName(tmp);
        runningFrames->addObject(frame);
    }

    CCAnimation *runningAnimation = CCAnimation::createWithSpriteFrames(runningFrames, 0.08f);
    sprite->runAction(CCRepeatForever::create(CCAnimate::create(runningAnimation)));

    addChild(sprite, 0);
}
