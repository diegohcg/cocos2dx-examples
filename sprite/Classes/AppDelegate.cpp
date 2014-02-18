#include "AppDelegate.h"

#include "MainLayer.h"

USING_NS_CC;

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

    CCScene *scene = createMainScene();
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

CCScene *AppDelegate::createMainScene()
{
    CCScene *scene = CCScene::create();
    MainLayer *layer = MainLayer::create();
    scene->addChild(layer);

    return scene;
}
