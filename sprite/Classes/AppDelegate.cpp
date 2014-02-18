#include "AppDelegate.h"

#include "MainLayer.h"

USING_NS_CC;

using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *director = CCDirector::sharedDirector();
    CCEGLView *eglView = CCEGLView::sharedOpenGLView();

    director->setOpenGLView(eglView);

    const CCSize &frameSize = eglView->getFrameSize();
    eglView->setDesignResolutionSize(frameSize.width, frameSize.height, kResolutionNoBorder);

    CCScene *scene = CCScene::create();
    CCLayer *layer = MainLayer::create();
    scene->addChild(layer);

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}
