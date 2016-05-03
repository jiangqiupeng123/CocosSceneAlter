//
//  newScene.cpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/21.
//
//

#include "NewScene.hpp"
#include "MyTool.hpp"
#include "ThirdScene.hpp"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

Scene *NewScene::createScene() {
    
    Scene *scene = Scene::create();
    NewScene *layer = NewScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool NewScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
//    array = Vector<Sprite *>();
    
    SimpleAudioEngine::getInstance()->playEffect("谭维维-如果有来生.mp3");
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("Spring.png");
    bg->setPosition(visibleSize / 2);
    bg->setScale(visibleSize.width / bg->getTextureRect().getMaxX(), visibleSize.height / bg-> getTextureRect().getMaxY());
    addChild(bg);
    
    // 雨滴粒子效果
    auto ps = ParticleRain::create();
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("rain.png"));
    ps->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
    addChild(ps);
    
    // 标签文字 Spring
    auto *lb = Label::createWithSystemFont("Spring", "fonts/Marker Felt.ttf", 50);
    addChild(lb);
    lb->setPosition(visibleSize / 2);
    
    this->scheduleOnce([this, visibleSize](float f){
        
//        CCTextureCache::sharedTextureCache()->removeTextureForKey("Winter.png");
        NewScene::showTime1(startImage, visibleSize, this);
        
    }, 10, "test");
    
    return true;
}

void NewScene::showTime1(CCInteger i, Size visibleSize, NewScene *myScene){
    
    static int num = i.getValue();
    int show1Num = 4;
    CCString *imgName = CCString::createWithFormat("image%d.png", i.getValue());
    Sprite *img = MyTool::createSpriteByNormalSizeWithName(imgName, 4, 4);
    auto nodeGrid = NodeGrid::create();
    nodeGrid->addChild(img);
    myScene->addChild(nodeGrid);
    img->setPosition(Vec2(-img->getBoundingBox().size.width / 2, visibleSize.height+img->getBoundingBox().size.height / 2));
    
    array.insert(array.size(), nodeGrid);
    
    float marginX = 200;    // X偏移量
    float marginY = 150;    // Y偏移量
    float marginRot = 10;   // 旋转偏移量
    
    img->runAction(Sequence::create(Spawn::create(MoveTo::create(1, Vec2(visibleSize.width / 2 - marginX * ((i.getValue() - num) % 2 ? -1 : 1), visibleSize.height / 2 + marginY * ((i.getValue() - num) / 2 ? -1 : 1))), RotateBy::create(1, 1080 + ((i.getValue() - num) % 3 ? marginRot : -marginRot)), NULL), CallFunc::create([this, myScene, i, visibleSize, show1Num](){
        
        CCInteger j = i.getValue() + 1;
        if (j.getValue() > num + show1Num - 1) {
            for (int i = 0; i < array.size(); i++) {
                NodeGrid *temp = array.at(i);
                
                temp->runAction(Sequence::create(DelayTime::create(2), TurnOffTiles::create(1, Size(100, 100)), CallFunc::create([temp, i, this, j, visibleSize, myScene](){
                    
                    temp->removeFromParent();
                    CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", i + num)->getCString());
                    
                    if (i == array.size() - 1) {
                        array.clear();
                        showTime2(j, visibleSize, myScene);
                    }
                    
                }), NULL));
            }
            return;
        }
        NewScene::showTime1(j, visibleSize, myScene);
        
        
    }),NULL));
    
}

void NewScene::showTime2(CCInteger i, Size visibleSize, NewScene *myScene) {
    static int num = i.getValue();
    int show2Num = 8;
    CCString *imgName = CCString::createWithFormat("image%d.png", i.getValue());
    Sprite *img = MyTool::createSpriteByNormalSizeWithName(imgName, 5, 5);
    auto nodeGrid = NodeGrid::create();
    nodeGrid->addChild(img);
    myScene->addChild(nodeGrid);
    
    img->setVisible(false);
    
    array.pushBack(nodeGrid);
    
    float marginX = 50;    // X偏移量
    float marginY = 30;    // Y偏移量
    float marginRot = 20;   // 旋转偏移量
    
    img->setPosition(200 + marginX * i.getValue(), visibleSize.height - 100 - marginY * i.getValue());
    
    img->setRotation(i.getValue() % 2 ? marginRot : -marginRot);
    
    img->runAction(Sequence::create(DelayTime::create(2), CallFunc::create([img](){
        
        img->setVisible(true);
        
    }), OrbitCamera::create(1.5, 1, 0, 0, 2160, 0, 0), DelayTime::create(3), CallFunc::create([this, i, visibleSize, myScene, show2Num](){
        
        CCInteger j = i.getValue() + 1;
        if (j.getValue() > num + show2Num - 1) {
            
            this->scheduleOnce([this](float){
                for (int n = 0; n < array.size(); n++) {
                    auto temp = array.at(n);
                    temp->removeFromParent();
                    CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("image%d.png", n + num)->getCString());
                }
            }, 2, "test");
            
            CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("rain.png")->getCString());
            Director::getInstance()->replaceScene(TransitionRotoZoom::create(2, ThirdScene::createSceneWithStartImage(j.getValue())));
            
            return;
        }
        NewScene::showTime2(j, visibleSize, myScene);
        
    }), NULL));
    
}
