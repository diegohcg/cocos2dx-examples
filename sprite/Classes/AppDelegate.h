#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <cocos2d.h>

USING_NS_CC;

class AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif
