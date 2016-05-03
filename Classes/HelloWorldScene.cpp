#include "HelloWorldScene.h"
#include "endScene.hpp"
#include "MyTool.hpp"
#include "ImageFadeOut.hpp"

Scene* HelloWorld::createSceneWithStartImage(int start)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    layer->startImage = start;
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _visibleSize = visibleSize;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Scene1背景
    auto bg = Sprite::create("Autumn.png");
    addChild(bg);
    bg->setPosition(visibleSize / 2);
    bg->setScale(visibleSize.width / bg->getTextureRect().getMaxX(), visibleSize.height / bg-> getTextureRect().getMaxY());
    
    // MoveBy, MoveTo
    // ->reverse() 反转
    
    // 标签文字
    auto *lb = Label::createWithSystemFont("Autumn", "fonts/Marker Felt.ttf", 50);
    addChild(lb);
    lb->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
    
    // 播放动画
    
    this->scheduleOnce([this, visibleSize](float f){
        
        showTime1(startImage, visibleSize, this);
        this->scheduleUpdate();
        CCTextureCache::sharedTextureCache()->removeTextureForKey("Summer.png");
//        showTime2(startImage);
        
    }, 2, "test");
    
//    // 进入Scene2
//    auto *listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = [this, lb](Touch *t, Event *e){
//        
//        if (lb->getBoundingBox().containsPoint(t->getLocation())) {
//            
//            this->scheduleOnce([this](float f){
//                
//                Director::getInstance()->replaceScene(TransitionRotoZoom::create(1, NewScene::createScene()));
//                
//            }, 1, "Test");
//            return false;
//        }
//        return false;
//        
//    };
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, lb);
    
    return true;
}



void HelloWorld::showTime1(CCInteger i, Size visibleSize, HelloWorld *myScene) {
    
    static int num = i.getValue();
    int show1Num = 11;
    _currentImgNum = i.getValue();
    
    if (i.getValue() >= num + show1Num) {
        _currentS1Img = NULL;
        this->scheduleOnce([this, i](float f){
            
            HelloWorld::showTime2(i.getValue());
            
        }, 6, "Test");
        return;
    }
    
    CCString *fileName = CCString::createWithFormat("image%d.png", i.getValue());
    Sprite *img = MyTool::createSpriteByNormalSizeWithName(fileName, 5, 5);
    _currentS1Img = img;
    myScene->addChild(img);
    
    img->setPosition(Vec2( -(img->getBoundingBox().size.width / 2), visibleSize.height / 2));
    img->runAction(Sequence::create(MoveBy::create(6, Vec2(visibleSize.width + img->getBoundingBox().size.width, 0)), CallFunc::create([this, i, img, show1Num](){
        
        img->removeFromParent();
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i.getValue())->getCString());
        
    }), NULL));
}

void HelloWorld::showTime2(int i) {
    
    static int num = i;
    int show2Num = 8;
    
    auto img = MyTool::createSpriteByNormalSizeWithName(CCString::createWithFormat("image%d.png", i), 6, 6);
    img->setPosition(Vec2(-300, 500));
    addChild(img);
    
    auto ps = ParticleMeteor::create();
    ps->setScale(10);
    ps->setPosition(img->getBoundingBox().size.width / 2, img->getBoundingBox().size.height / 2);
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("butterFly1.png"));
    img->addChild(ps);
    
    img->runAction(Sequence::create(MoveTo::create(0.5, Vec2(_visibleSize.width + 600, - 300)), MoveTo::create(0.5, Vec2(_visibleSize.width / 2, _visibleSize.height + 300)), MoveTo::create(0.5, Vec2(-300, -300)), MoveTo::create(0.5, _visibleSize / 2), CallFunc::create([ps, this](){
        
        ps->removeFromParentAndCleanup(true);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("butterFly1.png")->getCString());
        
    }), DelayTime::create(1), /*MoveTo::create(0.3, Vec2(_visibleSize.width + 300, _visibleSize.height + 300)),*/CallFunc::create([this, i, img](){
        
        img->setVisible(false);
        auto foImg = ImageFadeOut::create(CCString::createWithFormat("image%d.png", i)->getCString());
        foImg->setPosition(_visibleSize / 2);
        this->addChild(foImg);
        foImg->scheduleUpdate();
        
    }), DelayTime::create(0.5), CallFunc::create([this, i, show2Num, img](){
        
        if (i + 1 < num + show2Num) {
            HelloWorld::showTime2(i + 1);
        }
        else {
            
            Director::getInstance()->replaceScene(TransitionJumpZoom::create(2, endScene::createScene()));
            
        }
        
        img->removeFromParentAndCleanup(true);
        this->scheduleOnce([this, i](float f){
            
            CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i)->getCString());
            
        }, 5, "test");
        
    }), NULL));
    
}

void HelloWorld::update(float d) {
    
    if (!_currentS1Img) {
        this->unscheduleUpdate();
    }
    else {
        if (_currentS1Img->getPosition().x >= _visibleSize.width / 2) {
            CCInteger next = _currentImgNum + 1;
            showTime1(next, _visibleSize, this);
        }
    }
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
