#ifndef SPRITE_H
#define SPRITE_H

#include <cocos2d.h>

USING_NS_CC;

class Sprite : public CCSprite, public CCTargetedTouchDelegate
{
public:
    enum State {
        Idle,
        Running,
        Dying,
        ClimbingVertically,
        ClimbingHorizontally,
        Dazed,
        Fidget,
        LastState
    };

    Sprite();

    static Sprite* createWithSpriteFrame(CCSpriteFrame *spriteFrame);

    void setState(State state);
    State state() const { return m_state; }

    void nextState();

protected:
    void onEnter();
    void onExit();
    bool ccTouchBegan(CCTouch* touch, CCEvent* event);

private:
    void animate();
    inline void setFrames(State state, std::string stateName, int count);

    State m_state;
    std::map<int, int> m_frameCounts;
    std::map<int, std::string> m_frameNames;
};

#endif
