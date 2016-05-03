//
//  ThirdScene.hpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/22.
//
//

#ifndef ThirdScene_hpp
#define ThirdScene_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class ThirdScene:public Layer {
    
public:
    
    int startImage;
    virtual bool init();
    
    static Scene *createSceneWithStartImage(int start);
    
    CREATE_FUNC(ThirdScene);
    
    void showTime1(CCInteger i, Size visibleSize, ThirdScene *myScene);
    void showTime2(int i, Size visibleSize, ThirdScene *myScene);
    void showTime3(int i, Size visibleSize, ThirdScene *myScene);
    
};


#endif /* ThirdScene_hpp */
