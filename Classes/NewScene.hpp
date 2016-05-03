//
//  newScene.hpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/21.
//
//

#ifndef newScene_hpp
#define newScene_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class NewScene:public Layer {
    
public:
    Vector<NodeGrid *> array;
    virtual bool init();
    
    
    int startImage = 0;
    
    static Scene *createScene();
    
    CREATE_FUNC(NewScene);
    
    void showTime1(CCInteger i, Size visibleSize, NewScene *myScene);
    void showTime2(CCInteger i, Size visibleSize, NewScene *myScene);
};

#endif /* newScene_hpp */
