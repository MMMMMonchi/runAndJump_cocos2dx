#include "Background.h"
USING_NS_CC;

bool Background::init()
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    for(int i =0;i<2;i++){
        Sprite* bg=Sprite::create("background.png");
        float scaleX=visibleSize.width/bg->getContentSize().width;
        float scaleY=visibleSize.height/bg->getContentSize().height;
        bg->setScale(scaleX, scaleY);
        bg->setPosition(Point(visibleSize.width*i,visibleSize.height));
        bg->setAnchorPoint(Point(0,1));
        this->addChild(bg);
        _bgs->pushBack(bg);
    }
    return true;
};

void Background::update(float dt)
{
    Size visiblSize= Director::getInstance()->getVisibleSize();
    
    Sprite* leftBg;
    Sprite* rightBg;
    for(int i=0;i<2;i++){
        Sprite* bg= _bgs->at(i);
        float posX= bg->getPosition().x;
        if(posX > -640 && posX <= 0){
            leftBg = bg;
        }else{
            rightBg = bg;
        }
    }
    
    //左のみを動かし、右は左の位置を基準に配置
    leftBg->setPosition(Point(leftBg->getPosition().x-MOVE_SPEED*dt,leftBg->getPosition().y));
    rightBg->setPosition(Point(leftBg->getPosition().x+rightBg->getContentSize().width*rightBg->getScaleX(),leftBg->getPosition().y));
    if(leftBg->getPosition().x<=-visiblSize.width){
        leftBg->setPosition(Point(rightBg->getPosition().x+rightBg->getContentSize().width*rightBg->getScaleX(),visiblSize.height));
    }
};