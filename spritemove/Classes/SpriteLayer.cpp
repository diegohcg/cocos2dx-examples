#include "SpriteLayer.h"

#include "Sprite.h"
#include "CCSwipeGestureRecognizer.h"
#include "CCTapGestureRecognizer.h"
#include "CCLongPressGestureRecognizer.h"
#include "CCPanGestureRecognizer.h"

SpriteLayer::SpriteLayer()
    : m_sprite(0)
{
    //setTouchEnabled(true);
}

bool SpriteLayer::init()
{
    if (!CCLayer::init())
        return false;

    /*CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *background1 = CCSprite::create("background.png");
    CCSprite *background2 = CCSprite::create("background.png");
    CCPoint dustSpeed = ccp(0.1, 0.1);

    voidNode = CCParallaxNode::create();
    voidNode->addChild(background1, 0, dustSpeed, ccp(0,winSize.height/2));
    voidNode->addChild(background2, 0, dustSpeed, ccp(background1->getContentSize().width,winSize.height/2));
    addChild(voidNode);*/

    /*CCActionInterval *go = CCMoveBy::create(8, ccp(-1600, 0));
    CCActionInterval *goRev = CCMoveBy::create(8, ccp(1600, 0));
    CCActionInterval *seq = CCSequence::create(go, goRev, 0);
    voidNode->runAction(CCRepeatForever::create(seq));
    */
    createSprite();

    //scheduleUpdate();
    return true;
}

void SpriteLayer::update(float dt)
{
    CCLog("%s", __PRETTY_FUNCTION__);
    CCPoint backgroundScrollVert = ccp(-1600, 0);
    voidNode->setPosition(ccpAdd(voidNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
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

    addChild(m_sprite);

    CCSwipeGestureRecognizer *swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(SpriteLayer::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight
                        | kSwipeGestureRecognizerDirectionLeft
                        | kSwipeGestureRecognizerDirectionUp
                        | kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    addChild(swipe);

    CCTapGestureRecognizer *tap = CCTapGestureRecognizer::create();
    tap->setTarget(this, callfuncO_selector(SpriteLayer::didTap));
    tap->setNumberOfTapsRequired(1);
    tap->setCancelsTouchesInView(true);
    addChild(tap);

    /*
    CCTapGestureRecognizer *doubleTap = CCTapGestureRecognizer::create();
    doubleTap->setTarget(this, callfuncO_selector(SpriteLayer::didDoubleTap));
    doubleTap->setNumberOfTapsRequired(2);
    doubleTap->setCancelsTouchesInView(true);
    addChild(doubleTap);

    CCLongPressGestureRecognizer *longPress = CCLongPressGestureRecognizer::create();
    longPress->setTarget(this, callfuncO_selector(SpriteLayer::didLongPress));
    longPress->setMinimumPressDuration(0.6);
    longPress->setCancelsTouchesInView(true);
    addChild(longPress);

    CCPanGestureRecognizer * pan = CCPanGestureRecognizer::create();
    pan->setTarget(this, callfuncO_selector(SpriteLayer::didPan));
    pan->setCancelsTouchesInView(true);
    addChild(pan);*/
}

void SpriteLayer::didPan(CCObject *obj)
{
    CCLog("Pan");
}

void SpriteLayer::didLongPress(CCObject *obj)
{
    CCLog("Long Press");
}

void SpriteLayer::didTap(CCObject *obj)
{
    CCLog("Tap");
    CCTap *tap = static_cast<CCTap *>(obj);
    if (!tap)
        return;

    CCPoint pos = tap->location;
    CCPoint spritePos = m_sprite->getPosition();
    CCLog("x: %f, y: %f", pos.x, pos.y);
    float newX = pos.x - spritePos.x;
    m_sprite->runAction(CCMoveBy::create(0.05, ccp(newX, 0)));
}

void SpriteLayer::didDoubleTap(CCObject *obj)
{
    CCLog("Double Tap");
}

void SpriteLayer::didSwipe(CCObject *obj)
{
    CCLog("Swipe");

    CCSwipe *swipe = static_cast<CCSwipe *>(obj);
    if (!swipe)
        return;

    int direction = swipe->direction;
    switch(direction) {
        case kSwipeGestureRecognizerDirectionRight:
          CCLog("Swipe Right");
          m_sprite->runAction(CCMoveBy::create(0.05, ccp(50, 0)));
          break;
        case kSwipeGestureRecognizerDirectionLeft:
          CCLog("Swipe Left");
          m_sprite->runAction(CCMoveBy::create(0.05, ccp(-50, 0)));
          break;
        case kSwipeGestureRecognizerDirectionUp:
          CCLog("Swipe Up");
          break;
        case kSwipeGestureRecognizerDirectionDown:
          CCLog("Swipe Down");
          break;
    }
}
