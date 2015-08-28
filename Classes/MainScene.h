#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "GLES-Render.h"
#include "Runner.h"
#include "Background.h"
#include "MeterCounter.h"

#define PTM_RATIO 32.0

USING_NS_CC;

class MainScene : public Layer
{
public:
    
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    
    Point touchPoint;
    bool onTouchBegan(Touch* touch,cocos2d::Event* event);
    bool onContactBegin(PhysicsContact& contact);
    
private:
    
    Background* _backgroundLayer;
    MeterCounter* _meterCounter;
    
    static const int RUNNER_NUM=10;
    bool _mIsGrounded=false;
    
    float _proceedModifier=0.0f;
    
    Vector<Sprite*> _grounds[10];
    Vector<Runner*> _runners[RUNNER_NUM];
    Point _lastGroundPoint;
    void update(float dt);
    
    void initializeMetorCounter();
    void initializeRunner();
    void initializeGround();
    void initializeBg();
    
    void updateMetorCounter();
    void updateRunner(float dt);
    void updateGround(float dt);
    void updateBg(float dt);
    
    void checkFinishing();
    void finish();
};

#endif // __MainScene_SCENE_H__
