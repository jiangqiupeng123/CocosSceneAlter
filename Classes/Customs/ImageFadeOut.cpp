//
//  ImageFadeOut.cpp
//  CocosData
//
//  Created by 江秋朋 on 16/1/4.
//
//

#include "ImageFadeOut.hpp"
#include "MyTool.hpp"

ImageFadeOut::ImageFadeOut():_pointA(0), _pointB(0) {
    
}

ImageFadeOut::~ImageFadeOut() {
    
}

ImageFadeOut *ImageFadeOut::create(std::string image) {
    auto imageFadeOut = new ImageFadeOut();
    if (imageFadeOut == nullptr || imageFadeOut->initWithImage(image) == false) {
        CC_SAFE_DELETE(imageFadeOut);
        return nullptr;
    }
    return imageFadeOut;
}

bool ImageFadeOut::initWithImage(std::string image) {
    if (Node::init() == false) {
        return false;
    }
    
    auto ps = ParticleSystemQuad::create("fire.plist");
    ps->setAutoRemoveOnFinish(true);
    _pbn = ParticleBatchNode::createWithTexture(ps->getTexture());
    addChild(_pbn, 10);
    _imgName = image;
    _image = new Image();
    _image->initWithImageFile(image);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _displayClipping = DrawNode::create();
    auto display = MyTool::createSpriteByNormalSizeWithName(CCString::create(image), 6, 6);
    display->setAnchorPoint(Vec2(0, 0));
    this->setContentSize(display->getBoundingBox().size);
    
    Vec2 points[4];
    points[0] = Vec2(0, 0);
    points[1] = Vec2(0, this->getContentSize().height);
    points[2] = this->getContentSize();
    points[3] = Vec2(this->getContentSize().width, 0);
    
    _displayClipping->drawPolygon(points, 4, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0, Color4F(0, 0, 0, 0));
    _displayClipping->setAnchorPoint(Vec2(0, 0));
    _displayClipping->setContentSize(this->getContentSize());
    
    _displayImage = ClippingNode::create(_displayClipping);
    _displayImage->addChild(display);
    
    addChild(_displayImage);
    
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    _pointA = _pointB = this->getContentSize().width + this->getContentSize().height;
    
    return true;
}

void ImageFadeOut::update(float d) {
    const int step = 25;
    
    if (_pointA == 0) {
        this->unscheduleUpdate();
        scheduleOnce([this](float f){
            this->removeFromParentAndCleanup(true);
        }, 3, "test");
        return;
    }
    
    _pointA -= step;
    _pointB -= step;
    
    if (_pointA < 0) {
        _pointA = 0;
    }
    
    // 计算切割线段两个顶点的位置
    Vec2 pA(
        _pointA > this->getContentSize().width ? 0 : this->getContentSize().width - _pointA,
        _pointA > this->getContentSize().width ? this->getContentSize().height - (_pointB - this->getContentSize().width) : this->getContentSize().height
    );
    
    Vec2 pB(
        _pointB > this->getContentSize().height ? this->getContentSize().width - (_pointB - this->getContentSize().height) : this->getContentSize().width,
        _pointB > this->getContentSize().height ? 0 : this->getContentSize().height - _pointB
    );
    
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    
    // 计算切割模版的点
    Vec2 points[5];
    int pointCount = 0;
    if (_pointA > width) {
        points[pointCount++] = pA;
        points[pointCount++] = Vec2(0, height);
        points[pointCount++] = this->getContentSize();
    }
    else {
        points[pointCount++] = pA;
        points[pointCount++] = this->getContentSize();
    }
    if (_pointB > height) {
        points[pointCount++] = Vec2(width, 0);
        points[pointCount++] = pB;
    }
    else {
        points[pointCount++] = pB;
    }
    
    _displayClipping->clear();
    _displayClipping->drawPolygon(points, pointCount, Color4F(1.0f, 1.0f, 1.0f, 1.0f), 0, Color4F(0, 0, 0, 0));
    
    // 遍历AB两点组成的线段上的像素 创建粒子特效
    int x = pA.x , y = pA.y;
    auto pixel = (unsigned int *)(_image->getData());
    while (x < pB.x && y > 0) {
        x += step;
        y -= step;
        
        auto colorCode = pixel + (static_cast<unsigned int>(height - y - 1) * _image->getWidth()) + x;
        
        // 过滤透明像素
        if ((*colorCode>>24&0xff) == 0x00) {
            continue;
        }
        
        Color4F color(
            (*colorCode&0xff) / 255.0f,
            (*colorCode>>8&0xff) / 255.0f,
            (*colorCode>>16&0xff) / 255.0f,
            1.0f
        );
        
        auto p = ParticleSystemQuad::create("fire.plist");
        p->setStartColor(color);
        p->setEndColor(color);
        p->setAutoRemoveOnFinish(true);
        p->setPosition(Vec2(x + 15, y + 15));
        _pbn->addChild(p);
    }
    
}

void ImageFadeOut::onExit() {
    Node::onExit();
    _pbn->removeFromParentAndCleanup(true);
    _pbn = NULL;
    
}

//void ImageFadeOut::deletePartical(float delta, Node *ps) {
//    scheduleOnce([ps](float f){
//        ps->removeFromParentAndCleanup(true);
//    }, delta, "test");
//}





