//
//  MyTool.hpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/21.
//
//

#ifndef MyTool_hpp
#define MyTool_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class MyTool {

public:
    // 缩放图片
    static Sprite * createSpriteByNormalSizeWithName(CCString *str, int SCX, int SCY);
    
    virtual bool init();
    static MyTool *create();
};

#endif /* MyTool_hpp */
