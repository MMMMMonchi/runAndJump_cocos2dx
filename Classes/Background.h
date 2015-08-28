#ifndef __MyCppGame__Background__
#define __MyCppGame__Background__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Background:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(Background);
    void update(float dt);
private:
    static const int MOVE_SPEED = 64;
   Vector<Sprite*> _bgs[2];
};

#endif /* defined(__MyCppGame__Background__) */
