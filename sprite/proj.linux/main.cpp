#include <cocos2d.h>

#include "AppDelegate.h"

#define WIDTH 800
#define HEIGHT 480

USING_NS_CC;

int main(int argc, char *argv[])
{
    AppDelegate app;

    CCEGLView *eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(WIDTH, HEIGHT);

    return CCApplication::sharedApplication()->run();
}
