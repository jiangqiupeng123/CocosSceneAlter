//
//  ImageFadeOut.hpp
//  CocosData
//
//  Created by 江秋朋 on 16/1/4.
//
//

#ifndef ImageFadeOut_hpp
#define ImageFadeOut_hpp

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

#define ads 1

class ImageFadeOut:public Node {
    
protected:
    ClippingNode *_displayImage;
    DrawNode *_displayClipping;
    ParticleBatchNode *_pbn;
    
    Image *_image;
    std::string _imgName;
    
    // 两个运动的点
    int _pointA;
    int _pointB;
    
public:
    ImageFadeOut();
    virtual ~ImageFadeOut();
    static ImageFadeOut *create(std::string image);
    
    bool initWithImage(std::string image);
    
    virtual void update(float d);
    
    void onExit();
    
//    void deletePartical(float delta, Node *ps);
    
};

#endif /* ImageFadeOut_hpp */
