#include "Runner.h"
USING_NS_CC;

Runner* Runner::create(Point point){
    Runner *pRet = new Runner();
    if (pRet && pRet->init(point))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Runner::init(Point point){

    if ( !Sprite::initWithSpriteFrameName("slice01_01.png") )
    {
        return false;
    }
    
    SpriteFrameCache* frameCache=SpriteFrameCache::getInstance();
    Animation* animation=Animation::create();
    _mPrevPosition=point;
    
    for(int i=1;i<=19;i++){
        std::string fileId;
        if(i<10){
            fileId="slice0%d_0%d.png";
        }else{
            fileId="slice%d_%d.png";
        }
        std::string filename=StringUtils::format(fileId.c_str(),i,i);
        
        SpriteFrame* frame=frameCache->getSpriteFrameByName(filename);
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(0.05f);
    animation->setRestoreOriginalFrame(true);
    
    Animate* action=Animate::create(animation);
    RepeatForever* anime=RepeatForever::create(action);
    
    PhysicsBody* runnerPB=PhysicsBody::createBox(Size(this->getContentSize().width*0.1,this->getContentSize().height*1.1));
    runnerPB->setEnable(false);
    runnerPB->setMass(1.0f);
    runnerPB->setVelocity(Vect(0,1));
    runnerPB->setRotationEnable(false);
    runnerPB->setContactTestBitmask(1);
    //runnerPB->setAngularVelocityLimit(10.0f);
    
    this->setPosition(point);
    this->setPhysicsBody(runnerPB);
    this->runAction(anime);
    
    return true;
}

bool Runner::isGrounded(){
    return _mIsGrounded;
}
void Runner::setGroundedFlag(bool isGrounded){
    _mIsGrounded=isGrounded;
}

Point Runner::getPrevPosition(){
    return _mPrevPosition;
}
void Runner::setPrevPosition(){
    _mPrevPosition=this->getPosition();
}

void Runner::setGravityEnable(bool isEnable){
    this->getPhysicsBody()->setGravityEnable(isEnable);
}

