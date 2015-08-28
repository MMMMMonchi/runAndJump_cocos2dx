#include "MainScene.h"
#include <stdio.h>

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    //重力をシーンに設定
    Vect gravity;
    gravity.setPoint(0, -50);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSpeed(6.0f);
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initializeBg();
    initializeRunner();
    initializeGround();
    initializeMetorCounter();
    
    //タップのリスナー設定
    EventListenerTouchOneByOne* taplistener = EventListenerTouchOneByOne::create();
    taplistener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(taplistener, this);
    
    EventListenerPhysicsContact* contactlistener = EventListenerPhysicsContact::create();
    contactlistener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactlistener, this);
    
    return true;
}

bool MainScene::onTouchBegan(Touch *touch, Event *event)
{
    Runner* runner = _runners->at(0);
    if(runner->getPhysicsBody()->isEnabled() == false)
    {
        runner->getPhysicsBody()->setEnable(true);
    }
    if(runner->isVisible() == false)
    {
        
        _proceedModifier = 0.0f;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Runner* invisibleRunner;
        for(int i = 0; i < RUNNER_NUM; i++){
            invisibleRunner = _runners->at(i);
            invisibleRunner->setVisible(true);
            invisibleRunner->setPosition(Point(visibleSize.width/2, 400 + (visibleSize.height - 400) / RUNNER_NUM * (i+1)));
            invisibleRunner->getPhysicsBody()->setVelocity(Vec2(0, 1.0f));
            
            if(i == 0){
                invisibleRunner->setPosition(Point(visibleSize.width/2, visibleSize.height));
            }
        }
        scheduleUpdate();
    }
    else
    {
        
        if(runner->isGrounded())
        {
            runner->setGroundedFlag(false);
            runner->getPhysicsBody()->applyImpulse(Vect(0, 180.0f + _proceedModifier), Point(0, runner->getContentSize().height * -1));
        }
    }
    return true;
}

bool MainScene::onContactBegin(PhysicsContact& contact)
{
    Runner* runner = _runners->at(0);
    runner->setGroundedFlag(true);
    return true;
}

void MainScene::update(float dt)
{
    _proceedModifier += 0.1;
    
    updateMetorCounter();
    updateBg(dt);
    updateGround(dt);
    updateRunner(dt);
    checkFinishing();
}

void MainScene::initializeMetorCounter()
{
    _meterCounter = MeterCounter::create();
    this->addChild(_meterCounter);
}

void MainScene::updateMetorCounter()
{
    Runner* runner = _runners->at(0);
    _meterCounter->update(runner->getPosition().y);
}

void MainScene::initializeRunner()
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("runner.plist");
    
    for(int i = 0; i < RUNNER_NUM; i++)
    {
        Runner* runner = Runner::create(Point(visibleSize.width / 2,400 + (visibleSize.height - 400) / RUNNER_NUM * (i+1)));
        if(i != 0)
        {
            runner->setGravityEnable(false);
            runner->getPhysicsBody()->setEnable(false);
        }
        runner->setVisible(false);
        this->addChild(runner);
        _runners->pushBack(runner);
    }
}

void MainScene::updateRunner(float dt)
{
    for(int i = 0; i < RUNNER_NUM; i++)
    {
        Runner* runner=_runners->at(i);
        if(i == 0)
        {
            runner->setPrevPosition();
        }
        else
        {
            runner->setPrevPosition();
            runner->setPosition(_runners->at(i - 1)->getPrevPosition());
        }
    }
}

void MainScene::initializeBg()
{
    
    _backgroundLayer = Background::create();
    this->addChild(_backgroundLayer);
}

void MainScene::updateBg(float dt)
{
    _backgroundLayer->update(dt);
}

void MainScene::initializeGround()
{
    
    for(int i = 0; i < 10; i++){
        Sprite* ground = Sprite::create("ground.png");
        PhysicsBody* groundPB = PhysicsBody::createBox(Size(ground->getContentSize().width*0.2f,ground->getContentSize().height*0.2f));
        groundPB->setDynamic(false);
        groundPB->setEnable(true);
        groundPB->setContactTestBitmask(1);
        
        //地面の重力作成
        ground->setPosition(Point(700*i, 32));
        ground->setScale(0.2f, 0.2f);
        ground->setAnchorPoint(Point(0, 0));
        ground->setPhysicsBody(groundPB);
        this->addChild(ground);
        
        if(i==9){
            _lastGroundPoint=Point(ground->getPosition().x, ground->getPosition().y);
        }
        
        _grounds->pushBack(ground);
    }
}

void MainScene::updateGround(float dt)
{
    
    //地面の移動
    for(int i=0;i<10;i++)
    {
        Sprite* ground=_grounds->at(i);
        ground->setPosition(Point(ground->getPosition().x - 250*dt,ground->getPosition().y));
        
        if(ground->getPosition().x < -300)
        {
            ground->setPosition(_lastGroundPoint);
        }
    }
}

void MainScene::checkFinishing()
{
    
    bool isFinished = true;
    for(int i = 0; i < RUNNER_NUM; i++)
    {
        Runner* runner = _runners->at(i);
        if(runner->getPosition().y > -100)
        {
            isFinished = false;
        }
    }
    
    if(isFinished)
    {
        unscheduleUpdate();
        finish();
    }
}

void MainScene::finish()
{
    for(int i = 0; i < RUNNER_NUM; i++)
    {
        Runner* runner=_runners->at(i);
        runner->setVisible(false);
    }
}