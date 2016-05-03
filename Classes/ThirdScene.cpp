//
//  ThirdScene.cpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/22.
//
//

#include "ThirdScene.hpp"
#include "MyTool.hpp"
#include "HelloWorldScene.h"

Scene *ThirdScene::createSceneWithStartImage(int start) {
    
    auto scene = Scene::create();
    auto layer = ThirdScene::create();
    layer->startImage = start;
    scene->addChild(layer);
    return scene;
}

bool ThirdScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //背景
    auto bg = Sprite::create("Summer.png");
    bg->setPosition(visibleSize / 2);
    bg->setScale(visibleSize.width / bg->getTextureRect().getMaxX(), visibleSize.height / bg-> getTextureRect().getMaxY());
    addChild(bg);
    
    // 标签文字 Summer
    auto *lb = Label::createWithSystemFont("Summer", "fonts/Marker Felt.ttf", 50);
    addChild(lb);
    lb->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    
    this->scheduleOnce([this, visibleSize](float f){
        
        ThirdScene::showTime1(startImage, visibleSize, this);
        CCTextureCache::sharedTextureCache()->removeTextureForKey("Spring.png");
        
    }, 2, "test");
    
    
    return true;
}

void ThirdScene::showTime1(CCInteger i, Size visibleSize, ThirdScene *myScene) {
    
    static int num = i.getValue();
    int show1Num = 3;
    
    for (int j = num; j < num + show1Num; j++) {
        
        auto img = MyTool::createSpriteByNormalSizeWithName(CCString::createWithFormat("image%d.png", j), 5, 5);
        myScene->addChild(img);
        
        float imgW = img->getBoundingBox().size.width;
        float imgH = img->getBoundingBox().size.height;
        float margin = (visibleSize.width - imgW * 3) / 4;
        img->setPosition(Vec2(margin + imgW / 2 + (margin + imgW) * (j - num), visibleSize.height / 2 + (imgH / 2 + visibleSize.height / 2) * ((j - num) % 2 ? -1 : 1)));
        
        img->runAction(Sequence::create(MoveBy::create(10, Vec2(0, (visibleSize.height + imgH) * ((j - num) % 2 ? 1 : -1))), CallFunc::create([img, this, j, visibleSize, myScene, show1Num](){
            
            img->removeFromParent();
            CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", j)->getCString());
            if (j >= num + show1Num - 1) {
                this->scheduleOnce([this, j, visibleSize, myScene](float f){
                    
                    ThirdScene::showTime2(j + 1, visibleSize, myScene);
                    
                }, 2, "test");
            }
            
        }), NULL));
    }
}

void ThirdScene::showTime2(int i, Size visibleSize, ThirdScene *myScene) {
    static int num = i;
    static bool isFirst = true;
    int show2Num = 8;
    
    auto img = MyTool::createSpriteByNormalSizeWithName(CCString::createWithFormat("image%d.png", i), 7, 7);
    
    if (isFirst) {
        isFirst = false;
        addChild(img);
        img->setPosition(Vec2(-img->getBoundingBox().size.width / 2, img->getBoundingBox().size.height / 2 + visibleSize.height / 2));
        img->runAction(Sequence::create(JumpTo::create(2, visibleSize / 2, 300, 3), DelayTime::create(1), CallFunc::create([i, visibleSize, myScene, this, img](){
            
            img->removeFromParent();
            CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i)->getCString());
            ThirdScene::showTime2(i, visibleSize, myScene);
            
        }), NULL));
        return;
    }
    
    Sprite *nextImage = NULL;
    if (i + 1 < num + show2Num) {
        auto img2 = MyTool::createSpriteByNormalSizeWithName(CCString::createWithFormat("image%d.png", i + 1), 7, 7);
        img2->setPosition(visibleSize / 2);
        addChild(img2);
        nextImage = img2;
    }
    
    NodeGrid *ng = NodeGrid::create();
    ng->addChild(img);
    addChild(ng);
    
    img->setPosition(visibleSize / 2);
    
    ng->runAction(Sequence::create(DelayTime::create(3) ,Spawn::create(PageTurn3D::create(1, Size(50, 50)), CallFunc::create([img, i, this, visibleSize, myScene, show2Num](){
        
        int j = i + 1;
        if (j > num + show2Num - 1) {
            
            this->scheduleOnce([j, visibleSize, myScene, this](float f){
                ThirdScene::showTime3(j, visibleSize, myScene);
            }, 2, "test");

            return;
        }
        
    }), NULL), CallFunc::create([img, this, i, show2Num, nextImage, visibleSize, myScene](){
        
        img->removeFromParentAndCleanup(true);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i)->getCString());
        
        if (nextImage) {
            nextImage->removeFromParentAndCleanup(true);
            ThirdScene::showTime2(i + 1, visibleSize, myScene);
        }
        
        
    }), NULL));
    
}

void ThirdScene::showTime3(int i, Size visibleSize, ThirdScene *myScene) {
    
    static int num = i;
    int show3Num = 8;
    
    auto img = MyTool::createSpriteByNormalSizeWithName(CCString::createWithFormat("image%d.png", i), 6, 6);
    auto ng = NodeGrid::create();
    ng->addChild(img);
    addChild(ng);
    ng->setPosition(Vec2( -img->getBoundingBox().size.width / 2, visibleSize.height/2));
//    img->setRotation(-20 + random(0, 40));
    ng->runAction(Sequence::create(JumpTo::create(2, Vec2(visibleSize.width / 2 - 200 + random(0, 400), visibleSize.height / 2 - 100 + random(0, 200)), 300, 3), DelayTime::create(3), MoveTo::create(0.2, Vec2(visibleSize.width + 300, i % 2 ? visibleSize.height + 300 : -300)), CallFunc::create([img, i, this](){
        
        img->removeFromParentAndCleanup(true);
        CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i)->getCString());
    
    }), DelayTime::create(1), CallFunc::create([i, this, show3Num, myScene, visibleSize, ng](){
        
        
        if (i + 1 >= num + show3Num) {

            Director::getInstance()->replaceScene(TransitionRotoZoom::create(2, HelloWorld::createSceneWithStartImage(i + 1)));
            
            return;
        }
        ng->removeFromParent();
        showTime3(i + 1, visibleSize, myScene);
        
    }), NULL));
    
}
