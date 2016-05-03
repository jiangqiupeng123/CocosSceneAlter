//
//  MyTool.cpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/21.
//
//

#include "MyTool.hpp"

bool MyTool::init() {
    return true;
}

MyTool *MyTool::create() {
    MyTool *tool = new MyTool();
    return tool;
}

#pragma mark - 缩放图片至合适的尺寸
Sprite * MyTool::createSpriteByNormalSizeWithName(CCString *str, int SCX, int SCY) {
    Sprite *sp = Sprite::create(str->getCString());
    
    float spx = sp->getTextureRect().getMaxX();
    float spy = sp->getTextureRect().getMaxY();
    float scw = spx > spy ? 96 * SCX : 64 * SCY;//判断缩放后的宽度
    float sch = spx > spy ? 64 * SCY : 96 * SCX;//判断缩放后的高度
    
    sp->setScale(scw / spx, sch / spy);
    
    return sp;
}