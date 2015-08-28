#ifndef __MyCppGame__MeterCounter__
#define __MyCppGame__MeterCounter__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class MeterCounter:public Layer
{
    
public:
    virtual bool init();
    CREATE_FUNC(MeterCounter);
    void update(float currentRunnerPosY);
private:
    Label* _mMetorCounterLabel;
    int _mMaxMetor=0;
};

#endif /* defined(__MyCppGame__MeterCounter__) */
