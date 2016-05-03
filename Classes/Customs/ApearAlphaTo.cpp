//
//  ApearAlphaTo.cpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/23.
//
//

#include "ApearAlphaTo.hpp"

ApearAlphaTo *ApearAlphaTo::create(float duration, GLubyte opacity) {
    
    ApearAlphaTo *aa = new ApearAlphaTo();
    aa->init(duration, opacity);
    aa->autorelease();
    
    return aa;
}

bool ApearAlphaTo::init(float duration, GLubyte opacity) {
    
    if (ActionInterval::initWithDuration(duration)) {
        
        _opacity = opacity;
        
        return true;
    }
    
    return false;
}

void ApearAlphaTo::update(float time) {
    
    auto node = getTarget();
    GLubyte by = node->getOpacity();
    node->setOpacity(node->getOpacity() + 5);
    if (node->getOpacity() >= _opacity) {
        node->setOpacity(_opacity);
        stop();
    }
    
    
}

