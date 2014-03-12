#include "SpriteLayer.h"

#include "Sprite.h"
#include "CCSwipeGestureRecognizer.h"
#include "CCTapGestureRecognizer.h"
#include "CCLongPressGestureRecognizer.h"
#include "CCPanGestureRecognizer.h"

int scrollSpeed = 328;
CCSize winSize = ccp(800/2, 480/2);//CCDirector::sharedDirector()->getWinSize();// / 2;

SpriteLayer::SpriteLayer()
    : m_sprite(0)
    , m_vel(5)
{
    //setTouchEnabled(true);
}

bool SpriteLayer::init()
{
    if (!CCLayer::init())
        return false;

    //node = CCParallaxNode::create();

    m_bgMap.insert(std::pair<int, CCSprite*>(1, CCSprite::create("background.png")));
    m_bgWidth = m_bgMap.at(1)->getContentSize().width;
    CCLog("m_bgWidth: %f", m_bgWidth);
    m_bgMap.insert(std::pair<int, CCSprite*>(2, CCSprite::create("background.png")));
    m_bgMap.insert(std::pair<int, CCSprite*>(3, CCSprite::create("background.png")));

    m_bgMap.at(1)->setAnchorPoint(ccp(0, 0));
    m_bgMap.at(1)->setPosition(ccp(0, 0));
    addChild(m_bgMap.at(1), 0);

    m_bgMap.at(2)->setAnchorPoint(ccp(0, 0));
    m_bgMap.at(2)->setPosition(ccp(m_bgWidth, 0));
    addChild(m_bgMap.at(2), 0);

    m_bgMap.at(3)->setAnchorPoint(ccp(0, 0));
    m_bgMap.at(3)->setPosition(ccp(2 * (m_bgWidth), 0));
    addChild(m_bgMap.at(3), 0);

    createSprite();

    scheduleUpdate();

    return true;
}

void SpriteLayer::update(float dt)
{
    updateBg(m_vel);
}

void SpriteLayer::updateBgPosition(CCSprite* pBg, int updateSteps, float dt)
{
    if(pBg) {
		CCPoint bgPos = pBg->getPosition();
        CCLog("bgPx: %p %f %f", pBg, bgPos.x, m_bgWidth);
		//bgPos.x -= updateSteps;
		//float bgWidth = pBg->boundingBox().size.width;
		if (bgPos.x < -1600) {
            CCLog("xyz");
			bgPos.x = 2 * 1600;// - (2 * updateSteps);
			// To remove a black line between third and first part of the background,
			// after the first part has been moved to the right,
			// the part needs to be detached from the layer and added again.
			// This will move the first part on top of the others.
			// The object needs to be retained as removeChild would delete the object.
			pBg->retain();
			removeChild(pBg, false);
		    node->addChild(pBg, -1, ccp(5, 0), bgPos);
		};
		//pBg->setPosition(bgPos);
        //pBg->runAction(CCMoveTo::create(0, ccp(bgPos.x, bgPos.y)));
	}
}

void SpriteLayer::scrollBackground(float scrollSpeed)
{
    //CCActionInterval *go = CCMoveBy::create(scrollSpeed, ccp(-100,  0));
    //runAction(go);
    /*background1->setPosition(ccp( background1->getPosition().x - scrollSpeed,  background1->getPosition().y ));
itatic int x = 0;
    background2->setPosition(ccp( background2->getPosition().x  - scrollSpeed, background2->getPosition().y ));

    if(background1->getPosition().x<=-winSize.width) {
        float offset = background1->getPosition().x+winSize.width;
        background1->setPosition(ccp( winSize.width*3+offset, background1->getPosition().y  ));
    }
    if(background2->getPosition().x<=-winSize.width){
        float offset=background2->getPosition().x+winSize.width;
        background2->setPosition(ccp(winSize.width*3+offset, background2->getPosition().y  ));
    }*/
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
    m_sprite->setPosition(ccp(200, 100));
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

    /*CCPoint pos = tap->location;
    CCPoint spritePos = m_sprite->getPosition();
    CCLog("x: %f, y: %f", pos.x, pos.y);
    float newX = pos.x - spritePos.x;*/
    CCActionInterval *jump = CCJumpTo::create (0.5,
            ccp(m_sprite->getPosition().x, m_sprite->getPosition().y),
            200, 1);

    /*CCActionInterval *move = CCMoveTo::create(0.5, ccp(m_sprite->getPosition().x + 20,
                m_sprite->getPosition().y));*/
    //updateBg(30);
    m_sprite->runAction(CCSpawn::create(jump, NULL));
}

void SpriteLayer::didDoubleTap(CCObject *obj)
{
    CCLog("Double Tap");
}

void SpriteLayer::updateBg(int vel)
{
    m_bgMap.at(1)->setPosition(
        ccp(m_bgMap.at(1)->getPosition().x - vel, m_bgMap.at(1)->getPosition().y));
    m_bgMap.at(2)->setPosition(
            ccp(m_bgMap.at(2)->getPosition().x - vel, m_bgMap.at(2)->getPosition().y));
    m_bgMap.at(3)->setPosition(
            ccp(m_bgMap.at(3)->getPosition().x - vel, m_bgMap.at(3)->getPosition().y));

    if (m_bgMap.at(1)->getPosition().x < -m_bgWidth) {
        m_bgMap.at(1)->setPosition(
            ccp(m_bgMap.at(2)->getPosition().x + m_bgWidth, m_bgMap.at(2)->getPosition().y));
    }

    if (m_bgMap.at(2)->getPosition().x < -m_bgWidth) {
        m_bgMap.at(2)->setPosition(
            ccp(m_bgMap.at(3)->getPosition().x + m_bgWidth, m_bgMap.at(3)->getPosition().y));
    }

    if (m_bgMap.at(3)->getPosition().x < -m_bgWidth) {
        m_bgMap.at(3)->setPosition(
            ccp(m_bgMap.at(1)->getPosition().x + m_bgWidth, m_bgMap.at(1)->getPosition().y));
    }
}

void SpriteLayer::moveSprite(int steps)
{
    CCLog("moved");
    CCPoint p = m_sprite->getPosition();

    CCActionInterval *action = CCMoveTo::create(0.3, ccp(p.x + steps, p.y));
    CCActionInterval *action2 = CCMoveTo::create(2.0, ccp(200, 100));
    m_sprite->runAction(CCSequence::create(action, action2, NULL));
    moveBg(-steps);
}

void SpriteLayer::moveBg(int steps)
{
    unscheduleUpdate();
    m_bgMap.at(1)->runAction(
            CCMoveTo::create(0.3,
            ccp(m_bgMap.at(1)->getPosition().x + steps, m_bgMap.at(1)->getPosition().y)
            ));
    m_bgMap.at(2)->runAction(
            CCMoveTo::create(0.3,
            ccp(m_bgMap.at(2)->getPosition().x + steps, m_bgMap.at(2)->getPosition().y)
            ));
    m_bgMap.at(3)->runAction(
            CCMoveTo::create(0.3,
            ccp(m_bgMap.at(3)->getPosition().x + steps, m_bgMap.at(3)->getPosition().y)
            ));
    scheduleUpdate();
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
          /*m_sprite->runAction(CCSpawn::create(
          CCJumpTo::create (0.5,
              ccp(m_sprite->getPosition().x, m_sprite->getPosition().y),
              200, 1),
           CCRotateBy::create( 2,  720),
           NULL));*/
          break;
        case kSwipeGestureRecognizerDirectionDown:
          CCLog("Swipe Down");
          break;
    }

    CCPoint pAfter = m_sprite->getPosition();
    CCLog("pAfter (%f, %f)", pAfter.x, pAfter.y);
}
