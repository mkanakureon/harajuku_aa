#include "AppDelegate.h"
#include "HelloWorldScene.h"
//#include "HelloWorldScene2.h"

USING_NS_CC;

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(720, 1080);

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource_yoko  =  { cocos2d::CCSizeMake(1080, 720),   "iphone" };
static Resource smallResource_tate2  =  { cocos2d::CCSizeMake(720, 1080),   "iphone" };

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //
    CCSize frameSize = pEGLView->getFrameSize();
    CCLOG("applicationDidFinishLaunching frameSize.width = %f  frameSize.height= %f", frameSize.width,frameSize.height);
    if(frameSize.height/frameSize.width>1.4){
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedWidth);
    } else {
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
    }
    
    if(designResolutionSize.width == 720){
        pDirector->setContentScaleFactor( smallResource_tate2.size.width / designResolutionSize.width );    //縦
    } else {
        pDirector->setContentScaleFactor( smallResource_yoko.size.width / designResolutionSize.width );    //横
    }
    
    cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
    cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLOG("applicationDidFinishLaunching designResolutionSize.width = %f ", designResolutionSize.width);
    CCLOG("applicationDidFinishLaunching designResolutionSize.height = %f ", designResolutionSize.height);
    CCLOG("applicationDidFinishLaunching pDirector->getContentScaleFactor() = %f ", pDirector->getContentScaleFactor() );
    CCLOG("applicationDidFinishLaunching visibleSize  width=%f height=%f ", visibleSize.width, visibleSize.height );
    CCLOG("applicationDidFinishLaunching origin  x=%f y=%f ", origin.x, origin.y );

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();
    //CCScene *pScene = HelloWorld2::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
