#include "SpriteLayer.h"

#include "Sprite.h"
#include "CCSwipeGestureRecognizer.h"
#include "CCTapGestureRecognizer.h"
#include "CCLongPressGestureRecognizer.h"
#include "CCPanGestureRecognizer.h"

int scrollSpeed = 328;
CCSprite *background1, *background2;
CCSize winSize = ccp(800/2, 480/2);//CCDirector::sharedDirector()->getWinSize();// / 2;

SpriteLayer::SpriteLayer()
    : m_sprite(0)
{
    //setTouchEnabled(true);
}

bool SpriteLayer::init()
{
    if (!CCLayer::init())
        return false;

    background1 = CCSprite::create("background.png");
    background1->setPosition(ccp(0, 0));
    CCPoint point = CCDirector::sharedDirector()->convertToGL(ccp(0,0));
    CCLog("get scale: %lf, %lf", point.x, point.y);
    //background1->setFlipX(true);
    //background2 = CCSprite::create("background.png");
    //background2->setFlipX(true);

    background1->setPosition(ccp(winSize.width, winSize.height));
    //background2->setPosition(ccp(3*winSize.width, winSize.height));
    /*CCActionInterval *go = CCMoveBy::create(8, ccp(-1600, 0));
    CCActionInterval *goRev = CCMoveBy::create(8, ccp(1600, 0));
    CCActionInterval *seq = CCSequence::create(go, goRev, 0);
    voidNode->runAction(CCRepeatForever::create(seq));
    */
    //add them to main layer
    addChild(background1);
    //addChild(background2);
    createSprite();

    scheduleUpdate();
    return true;
}

void SpriteLayer::update(float dt)
{
    //CCLog("%s", __PRETTY_FUNCTION__);
    //scrollBackground(scrollSpeed*dt);
}

void SpriteLayer::scrollBackground(float scrollSpeed)
{
    //CCActionInterval *go = CCMoveBy::create(scrollSpeed, ccp(-100,  0));
    //runAction(go);
    background1->setPosition(ccp( background1->getPosition().x - scrollSpeed,  background1->getPosition().y ));
    background2->setPosition(ccp( background2->getPosition().x  - scrollSpeed, background2->getPosition().y ));

    if(background1->getPosition().x<=-winSize.width) {
        float offset = background1->getPosition().x+winSize.width;
        background1->setPosition(ccp( winSize.width*3+offset, background1->getPosition().y  ));
    }
    if(background2->getPosition().x<=-winSize.width){
        float offset=background2->getPosition().x+winSize.width;
        background2->setPosition(ccp(winSize.width*3+offset, background2->getPosition().y  ));
    }
}

void SpriteLayer::createSprite()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("Win Size: (%lf, %lf)", winSize.width, winSize.height);

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
