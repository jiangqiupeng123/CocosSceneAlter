#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    int startImage;
    Size _visibleSize;
    Sprite *_currentS1Img;
    int _currentImgNum;
    
    static cocos2d::Scene* createSceneWithStartImage(int start);
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void update(float d);
    
    // 显示图片
    void showTime1(CCInteger i, Size visibleSize, HelloWorld *myScene);
    void showTime2(int i);
    // 缩放图片
    Sprite * createSpriteByNormalSizeWithName(CCString *str);
};

#endif // __HELLOWORLD_SCENE_H__
