#include "Sprite.h"

Sprite::Sprite()
    : m_state(LastState)
{
    setFrames(Idle, "idle", 22);
    setFrames(Running, "running", 27);
    setFrames(Dying, "dying", 6);
    setFrames(ClimbingVertically, "climbing_vertically", 8);
    setFrames(ClimbingHorizontally, "climbing_horizontally", 8);
    setFrames(Dazed, "dazed", 8);
    setFrames(Fidget, "fidget_1", 9);
}

Sprite* Sprite::createWithSpriteFrame(CCSpriteFrame *spriteFrame)
{
    Sprite *sprite = new Sprite();
    if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame)) {
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return 0;
}

void Sprite::setState(State state)
{
    m_state = state;

    animate();
}

void Sprite::nextState()
{
    m_state = static_cast<State>((m_state + 1) % LastState);

    setState(m_state);
}

void Sprite::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void Sprite::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

/*bool Sprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    nextState();

    return true;
}*/

void Sprite::animate()
{
    stopAllActions();

    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* currentFrames = CCArray::create();
    CCSpriteFrame *frame;
    char tmp[50];

    for (int i = 0; i < m_frameCounts[m_state]; i++) {
        sprintf(tmp, "%s %d.png", m_frameNames[m_state].c_str(), i + 1);
        frame = cache->spriteFrameByName(tmp);
        if (!frame)
            continue;

        currentFrames->addObject(frame);
    }

    CCAnimation *currentAnimation = CCAnimation::createWithSpriteFrames(currentFrames, 0.08f);
    runAction(CCRepeatForever::create(CCAnimate::create(currentAnimation)));
}

void Sprite::setFrames(State state, std::string stateName, int count)
{
    m_frameNames[state] = stateName;
    m_frameCounts[state] = count;
}
