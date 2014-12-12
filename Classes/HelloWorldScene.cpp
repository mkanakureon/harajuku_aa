#include "HelloWorldScene.h"
#include <fstream>

#include "GHelper.h"

//#include "HttpRequest.h"

USING_NS_CC;

//USING_NS_CC_EXT;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLog("HelloWorld::init");
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
/***
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
***/
    
    GHelper::init();
    GHelper::cache->addSpriteFramesWithFile("sample.plist");
    
    CCSprite* pSprite  = CCSprite::create("bg_720_1080.png"); //１枚毎　ロゴ無し背景
    pSprite->setPosition( GHelper::CCPointMake720_1080(360, 640) );
    this->addChild(pSprite, 0);
    
    CCSprite* pSprite2  = CCSprite::create("bg_720_1080_2.png"); //１枚毎　ロゴ無し背景
    pSprite2->setPosition( GHelper::CCPointMake720_1080(0, 0) );
    this->addChild(pSprite2, 0);
    
    //720x1280の四隅
    CCSprite* hom1   = GHelper::createGSprite720_1280(0,0, "hom001.png");
    this->addChild(hom1, 0);
    
    CCSprite* hom2   = GHelper::createGSprite720_1280(720,0, "hom001.png");
    this->addChild(hom2, 0);
    
    CCSprite* hom3   = GHelper::createGSprite720_1280(720,1280, "hom001.png");
    this->addChild(hom3, 0);
    
    CCSprite* hom4   = GHelper::createGSprite720_1280(0,1280, "hom001.png");
    this->addChild(hom4, 0);
    
    //720x1080の四隅（）
    CCSprite* hom5   = GHelper::createGSprite720_1280(0,100, "hom011.png");
    this->addChild(hom5, 0);
    
    CCSprite* hom6   = GHelper::createGSprite720_1280(720,100, "hom011.png");
    this->addChild(hom6, 0);
    
    CCSprite* hom7   = GHelper::createGSprite720_1280(720,1280-100, "hom011.png");
    this->addChild(hom7, 0);
    
    CCSprite* hom8   = GHelper::createGSprite720_1280(0,1280-100, "hom011.png");
    this->addChild(hom8, 0);
    
    CCSprite* hom9   = GHelper::createGSprite720_1280(360,640, "hom001.png");
    this->addChild(hom9, 0);
    
    CCLog("HelloWorld::init end");
    
    
    return true;
}

bool HelloWorld::read_txt()
{
    CCLog("HelloWorld::read_csv");
    
    CCFileUtils *fileUtils = CCFileUtils::sharedFileUtils();
    std::string filePath = fileUtils->fullPathForFilename("csv.csv");
    unsigned long nSize = 0;
    unsigned char* pBuffer = fileUtils->getFileData(filePath.c_str(), "r", &nSize);
    CCLog("%s",pBuffer);
    delete[] pBuffer;
    
    return true;
}

bool HelloWorld::read_csv()
{
    CCLog("HelloWorld::read_csv");
    
    std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("csv.csv");
    CCLog("filePath=%s",filePath.c_str() );
    
    std::ifstream ifs(filePath.c_str());
    std::string csvLine;
    
    if(!ifs){
        CCLog("HelloWorld::readFile false");
        return false;
    }
    int i=0;
    while ( getline(ifs, csvLine) )
    {
        std::istringstream csvStream(csvLine);
        std::string csvCol;
        
        while ( getline(csvStream, csvCol, ',') ){
            if (atoi(csvCol.c_str()) != 0){
                CCLog("%d",atoi(csvCol.c_str()));
            }
        }
    }
    CCLog("HelloWorld::readFile end");
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    
    CCLog("HelloWorld::menuCloseCallback");
    //read_csv();
    read_txt();
    
    //startDownload("");
/***
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
***/
}

/**
 
 Authorization: ヘッダには、
 Basic認証の ID と PW とを :（半角のコロン）でつなげた文字列を、
 base64した値が格納さています。
 （例えば、
 　Authorization: Basic dXNlcjAxOnBhc3N3b3JkCg==　といったようになります。）
 
 Authorization: Basic dXNlcjAxOnBhc3N3b3JkCg==
 
 **/

void HelloWorld::startDownload(char const *url) {
    CCLog("HelloWorld::startDownload");    
    
    CCHttpRequest *request = new CCHttpRequest();
    request->setUrl("http://t18mkx.lolipop.jp/hapihomu/cg01");
    
    /***
    std::vector<std::string> h;
    h.push_back("X-Parse-Application-Id: SOME_ID");
    h.push_back("X-Parse-REST-API-Key: SOME_KEY");
    h.push_back("Content-Type: application/json");
    request->setHeaders(h);
     ***/
    
    //request->setUrl("http://www.google.co.jp/images/srpr/logo11w.png");
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
    CCHttpClient::getInstance()->send(request);
    request->release();
}



// コールバックメソッドの中で受信したファイルを保存する
void HelloWorld::onHttpRequestCompleted(CCNode *sender, void *data) {
    CCLog("HelloWorld::onHttpRequestCompleted");      
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCHttpResponse *response = (CCHttpResponse *)data;
    if (!response->isSucceed()) return;
    
    std::vector<char> *buffer = response->getResponseData();
    
    // 2. CCImageのinitWithImageDataで画像フォーマットを解析
    CCImage *image = new CCImage();
    image->initWithImageData(&(buffer->front()), buffer->size());
    
    // 3. CCTexture2DからCCSpriteへ
    CCTexture2D *texture = new CCTexture2D();
    texture->initWithImage(image);
    CCSprite *sprite = CCSprite::createWithTexture(texture);
    
    sprite->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(sprite);
    
    //
    
    //std::ofstream ofs;
    
    /***
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "image.png";
    CCLog("filePath.c_str() %s",filePath.c_str());
    //char *path = filePath.c_str();
    int outbf[10] = {1,2,3,4,5,6,7,8,9,10};
    int inbuf[10];
    
    FILE *fp = fopen(filePath.c_str(), "wb+");
    fwrite(outbf, sizeof(int), 10, fp);
    
    fseek(fp, 0L, SEEK_SET);
    fread(inbuf, sizeof(int), 10, fp);
    fclose(fp);
    
    for (int i=0; i<10; i++)
		printf("%3d",inbuf[i]);
	printf("\n");
    ***/
    
    //

    //書き込み
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "image.png";
    CCLog("filePath.c_str() %s",filePath.c_str());
    buffer = response->getResponseData();
    
    std::ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    ofs.write(&(buffer->front()), buffer->size());
    ofs.flush();
    ofs.close();

    //読み込み
    CCImage *image2 = new CCImage();
    if (image2 && image2->initWithImageFile(filePath.c_str(), CCImage::kFmtPng)) {
        CCTexture2D *texture = new CCTexture2D();
        if (texture && texture->initWithImage(image2)) {
            CCSprite *sprite = CCSprite::createWithTexture(texture);
            sprite->setPosition(ccp(240, 240));
            this->addChild(sprite);
        }
    }
    
}