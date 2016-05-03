//
//  endScene.hpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/23.
//
//

#ifndef endScene_hpp
#define endScene_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class endScene:public Layer {
    
public:
    int startImage;
    virtual bool init();
    
    static Scene *createScene();
    
    CREATE_FUNC(endScene);
    
};


#endif /* endScene_hpp */
