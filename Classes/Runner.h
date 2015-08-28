#ifndef __MyCppGame__Runner__
#define __MyCppGame__Runner__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Runner:public cocos2d::Sprite
{
    
public:
    virtual bool init(Point point);
    static Runner* create(Point point);
    bool isGrounded();
    void setGroundedFlag(bool isGrounded);
    
    Point getPrevPosition();
    void setPrevPosition();
    void setGravityEnable(bool isEnable);
    
private:
    bool _mIsGrounded=false;
    Point _mPrevPosition;
};

#endif /* defined(__MyCppGame__Runner__) */
