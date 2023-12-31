#include "AppDelegate.h"
#include "SceneMain.h"
#include "StartScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1300, 800);  // ��Ʒֱ��ʴ�СΪ1300x800���ء�

AppDelegate::AppDelegate()
{
}

// ���ݲ�ͬ����Ƶ����ѡ��ִ����Ӧ����Դ�ͷŲ���
AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// ���ڳ�ʼ��OpenGL����������
// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

// ����ע�����е���չ��
// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance(); //��ȡȫ��Ψһ�� Director ����ʵ��
    auto glview = director->getOpenGLView(); //��ȡ OpenGL ��ͼ����
    // ��� OpenGL ��ͼ�����Ƿ����
    // ��������ڣ�����ݲ�ͬ��ƽ̨����һ���µ� OpenGL ��ͼ
    // ����������Ϊ Director �� OpenGL ��ͼ
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Scene1", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Scene1");
#endif
        director->setOpenGLView(glview);
    }

    // ������Ϸ����ʱ��֡��Ϊ 60 ֡ÿ��
    director->setAnimationInterval(1.0f / 60);

    // �Թ̶��߶�Ϊ��׼���Զ������Ƚ������䣬���ܻ�ü�����ϵĲ������ݡ�
    glview->setDesignResolutionSize(1300, 800, ResolutionPolicy::SHOW_ALL);

    // ע������֧�ֵ���չ��
    register_all_packages();

    // ����һ���������󣬲���������Ϊ�Զ��ͷ�
    //auto scene = Scene1::createScene();

    auto startScene = StartScene::create();

    // run
    director->runWithScene(startScene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation(); // ֹͣ��Ϸ�Ķ�����Ⱦ

    // ѡ����Ӧ����Ƶ��������ͣ��Ƶ����
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation(); // ������Ϸ�Ķ�����Ⱦ

    // ѡ����Ӧ����Ƶ�������ָ���Ƶ����
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
