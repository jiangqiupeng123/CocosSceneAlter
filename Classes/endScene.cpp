//
//  endScene.cpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/23.
//
//

#include "endScene.hpp"
#include "NewScene.hpp"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

Scene *endScene::createScene() {
    
    Scene *scene = Scene::create();
    endScene *layer = endScene::create();
    scene->addChild(layer);
    return scene;
}

bool endScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("Winter.png");
    bg->setPosition(visibleSize / 2);
    bg->setScale(visibleSize.width / bg->getTextureRect().getMaxX(), visibleSize.height / bg-> getTextureRect().getMaxY());
    addChild(bg);
    
    // 标签文字
    auto *lb = Label::createWithSystemFont("Winter", "fonts/Marker Felt.ttf", 50);
    addChild(lb);
    lb->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 50));
    
    this->scheduleOnce([this, visibleSize](float f){
        
        CCTextureCache::sharedTextureCache()->removeTextureForKey("Autumn.png");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("fire.plist");
        
        SimpleAudioEngine::getInstance()->stopAllEffects();
        SimpleAudioEngine::getInstance()->playEffect("We wish you a Merry Christmas.mp3");
        
        // 雪花粒子效果
        auto ps = ParticleSnow::create();
        ps->setTexture(Director::getInstance()->getTextureCache()->addImage("snow.png"));
        ps->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
        addChild(ps);
        
        auto lb1 = Label::createWithSystemFont("Darling~Happy New Year!", "fonts/Marker Felt.ttf", 70);
        addChild(lb1);
        lb1->setPosition(Vec2(-400, visibleSize.height / 2));
        
        auto lb2 = Label::createWithSystemFont("Love You Forever♥️", "fonts/Marker Felt.ttf", 70);
        addChild(lb2);
        lb2->setPosition(Vec2(-300, visibleSize.height + 50));
        
        // Again按钮
        auto *againLb = Label::createWithSystemFont("Again", "fonts/Marker Felt.ttf", 50);
        addChild(againLb);
        againLb->setPosition(Vec2(100, visibleSize.height + 50));
        
        lb1->runAction(Sequence::create(DelayTime::create(2), JumpTo::create(2, Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 200), 200, 3), DelayTime::create(2), CallFunc::create([lb2, this, visibleSize, againLb](){
            
            lb2->runAction(Sequence::create(Spawn::create(RotateBy::create(2, 1080), MoveTo::create(2, Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100)), NULL), DelayTime::create(2), CallFunc::create([againLb, this, visibleSize](){
                
                againLb->runAction(MoveTo::create(0.5, Vec2(100, 100)));
                
            }), NULL));
            
        }), NULL));
        
        auto *listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this, againLb, ps](Touch *t, Event *e){
            
            if (againLb->getBoundingBox().containsPoint(t->getLocation())) {
                
                this->scheduleOnce([this, ps](float f){
                    
                    ps->removeFromParentAndCleanup(true);
                    CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("snow.png")->getCString());
                    
                }, 1, "test");
                
                SimpleAudioEngine::getInstance()->stopAllEffects();
                Director::getInstance()->replaceScene(TransitionRotoZoom::create(1, NewScene::createScene()));
                
            }
            return false;
            
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, againLb);
        
    }, 3, "test");
    
    return true;
}