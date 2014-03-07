#include "SpriteLayer.h"

#include "Sprite.h"
#include "CCSwipeGestureRecognizer.h"
#include "CCTapGestureRecognizer.h"
#include "CCLongPressGestureRecognizer.h"
#include "CCPanGestureRecognizer.h"

int scrollSpeed = 328;
CCSprite *background1, *background2, *background3;
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
    background1->setAnchorPoint(ccp(0, 0));
    background1->setPosition(ccp(0, 0));

    float bgWidth = background1->getContentSize().width;

    background2 = CCSprite::create("background.png");
    background2->setAnchorPoint(ccp(0, 0));
    background2->setPosition(ccp(bgWidth - 1, 0));

    background3 = CCSprite::create("background.png");
    background3->setAnchorPoint(ccp(0, 0));
    background3->setPosition(ccp(2 * (bgWidth - 1), 0));

    //CCPoint point = CCDirector::sharedDirector()->convertToGL(ccp(0,0));
    //CCLog("scale: %f, %f", point.x, point.y);
    //background1->setPosition(point);
    //background1->setFlipX(true);
    //background2 = CCSprite::create("background.png");
    //background2->setFlipX(true);

    //background1->setPosition(ccp(winSize.width, winSize.height));
    //background2->setPosition(ccp(3*winSize.width, winSize.height));
    /*CCActionInterval *go = CCMoveBy::create(8, ccp(-1600, 0));
    CCActionInterval *goRev = CCMoveBy::create(8, ccp(1600, 0));
    CCActionInterval *seq = CCSequence::create(go, goRev, 0);
    voidNode->runAction(CCRepeatForever::create(seq));*/

    //add them to main layer
    addChild(background1, 0);
    addChild(background2, 0);
    addChild(background3, 0);

    createSprite();

    scheduleUpdate();
    return true;
}

void SpriteLayer::update(float dt)
{
    int steps = 10;

    updateBg(steps);
    /*background1->runAction(
                CCMoveBy::create(0.5, ccp(-(2.5 * steps), 0))
            );
    background2->runAction(
                CCMoveBy::create(0.5, ccp(-(2.5 * steps), 0))
            );
    background3->runAction(
                CCMoveBy::create(0.5, ccp(-(2.5 * steps), 0))
            );*/
    //CCLog("%f %f %f", background1->getPosition().x
    //        , background2->getPosition().x
    //        , background3->getPosition().x);
    //CCLog("%s", __PRETTY_FUNCTION__);
    //scrollBackground(scrollSpeed*dt);
    //updateBgPosition(background1, 10);
    //updateBgPosition(background2, 10);
    //updateBgPosition(background3, 10);
}

void SpriteLayer::updateBgPosition(CCSprite* pBg, int updateSteps)
{
	if(pBg)
	{
		CCPoint bgPos = pBg->getPosition();
		bgPos.x -= updateSteps;
		float bgWidth = pBg->boundingBox().size.width;
		if(bgPos.x < -bgWidth)
		{
			bgPos.x = 2 * bgWidth - (2 * updateSteps);
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			pBg->retain();
			removeChild(pBg, false);
			addChild(pBg, 0);
		};
		pBg->setPosition(bgPos);
	}
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
    m_sprite->setPosition(ccp(200, 200));
    m_sprite->nextState();

    addChild(m_sprite, 1);

    CCSwipeGestureRecognizer *swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(SpriteLayer::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionRight
                        | kSwipeGestureRecognizerDirectionLeft
                        | kSwipeGestureRecognizerDirectionUp
                        | kSwipeGestureRecognizerDirectionDown);
    swipe->setCancelsTouchesInView(true);
    addChild(swipe);

    /*CCTapGestureRecognizer *tap = CCTapGestureRecognizer::create();
    tap->setTarget(this, callfuncO_selector(SpriteLayer::didTap));
    tap->setNumberOfTapsRequired(1);
    tap->setCancelsTouchesInView(true);
    addChild(tap);
    */
    /*
    CCTapGestureRecognizer *doubleTap = CCTapGestureRecognizer::create();
    doubleTap->setTarget(this, callfuncO_selector(SpriteLayer::didDoubleTap));
    doubleTap->setNumberOfTapsRequired(2);
    doubleTap->setCancelsTouchesInView(true);
    addChild(doubleTap);

    */
    CCLongPressGestureRecognizer *longPress = CCLongPressGestureRecognizer::create();
    longPress->setTarget(this, callfuncO_selector(SpriteLayer::didLongPress));
    longPress->setMinimumPressDuration(0.6);
    longPress->setCancelsTouchesInView(true);
    //addChild(longPress);

    /*
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
    //scheduleUpdate();
    //updateBg(500);
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

void SpriteLayer::updateBg(int steps)
{
    updateBgPosition(background1, steps);
    updateBgPosition(background2, steps);
    updateBgPosition(background3, steps);
}

void SpriteLayer::moveSprite(int steps)
{
    CCLog("moved");
    unscheduleUpdate();
    CCPoint p = m_sprite->getPosition();
    m_sprite->runAction(CCMoveTo::create(0.5, ccp(p.x + steps, p.y)));
    updateBg(steps);
    //scheduleUpdate();
}

void SpriteLayer::didSwipe(CCObject *obj)
{
    CCLog("Swipe");

    CCSwipe *swipe = static_cast<CCSwipe *>(obj);
    if (!swipe)
        return;

    int direction = swipe->direction;
    CCPoint pBefore = m_sprite->getPosition();
    CCLog("pBefore (%f, %f)", pBefore.x, pBefore.y);

    switch(direction) {
        case kSwipeGestureRecognizerDirectionRight:
          CCLog("Swipe Right");
          moveSprite(200);
          break;
        case kSwipeGestureRecognizerDirectionLeft:
          CCLog("Swipe Left");
          moveSprite(-200);
          break;
        case kSwipeGestureRecognizerDirectionUp:
          CCLog("Swipe Up");
          m_sprite->runAction(CCSpawn::create(
          CCJumpTo::create (0.5,
              ccp(m_sprite->getPosition().x, m_sprite->getPosition().y),
              200, 1),
           CCRotateBy::create( 2,  720),
           NULL));
          break;
        case kSwipeGestureRecognizerDirectionDown:
          CCLog("Swipe Down");
          break;
    }

    CCPoint pAfter = m_sprite->getPosition();
    CCLog("pAfter (%f, %f)", pAfter.x, pAfter.y);
}
