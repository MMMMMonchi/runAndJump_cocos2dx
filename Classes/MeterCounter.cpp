#include "MeterCounter.h"
USING_NS_CC;

bool MeterCounter::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _mMetorCounterLabel = Label::createWithSystemFont("記録:0m", "Arial" ,90);
    _mMetorCounterLabel->setColor(Color3B::WHITE);
    _mMetorCounterLabel->setPosition(Point(30,visibleSize.height - _mMetorCounterLabel->getContentSize().height));
    _mMetorCounterLabel->setAnchorPoint(Point(0,0));
    this->addChild(_mMetorCounterLabel);

    return true;
};

void MeterCounter::update(float currentRunnerPosY)
{
    if(currentRunnerPosY > _mMaxMetor)
    {
        _mMaxMetor = currentRunnerPosY;
    }
    else
    {
        return;
    }
    
    _mMetorCounterLabel->setString(StringUtils::format("記録:%dm",_mMaxMetor));
    if(_mMaxMetor >= 500 && _mMaxMetor < 1000)
    {
        _mMetorCounterLabel->setColor(Color3B::GREEN);
    }
    if(_mMaxMetor >= 1000 && _mMaxMetor < 2000)
    {
        _mMetorCounterLabel->setColor(Color3B::YELLOW);
    }
    if(_mMaxMetor >= 2000 && _mMaxMetor < 3000)
    {
        _mMetorCounterLabel->setColor(Color3B::RED);
    }
    if(_mMaxMetor >= 3000 && _mMaxMetor < 4000)
    {
        _mMetorCounterLabel->setColor(Color3B::MAGENTA);
    }
    if(_mMaxMetor >= 4000)
    {
        _mMetorCounterLabel->setColor(Color3B::MAGENTA);
    }
};