//
//  ApearAlphaTo.hpp
//  CocosSceneAlter
//
//  Created by 江秋朋 on 15/12/23.
//
//

#ifndef ApearAlphaTo_hpp
#define ApearAlphaTo_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class ApearAlphaTo:public ActionInterval {
    
public:
    
    float _opacity;
    
    static ApearAlphaTo *create(float duration, GLubyte opacity);
    
    bool init(float duration, GLubyte opacity);
    
    virtual void update(float time);
    
};

#endif /* ApearAlphaTo_hpp */
