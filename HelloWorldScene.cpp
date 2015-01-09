#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
		auto scene = Scene::createWithPhysics();
	
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	scene->getPhysicsWorld()->setGravity(Vect(0.0f,0.0f));
	// 'layer' is an autorelease object  
	auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	// add layer as a child to scene  
	scene->addChild(layer);
	
	// return the scene  
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	CCLog("init");
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

   

    /////////////////////////////
    // 3. add your codes below...

	//保存待删除的body
	arraybody = CCArray::create();
	arraysprite = CCArray::create();
	arraybody->retain();
	arraysprite->retain();

	//建立边界边框
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(body);
	this->addChild(edgeSp); 
	edgeSp->setTag(0);

	//建立地面
	/*auto groundsp = Sprite::create();
	auto groundbody = PhysicsBody::createBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT);
	groundbody->setDynamic(false);
	groundbody->getFirstShape()->setFriction(100.f);
	groundsp->setPosition(Point(visibleSize.width / 2-100, visibleSize.height / 2-100));
	groundsp->setPhysicsBody(groundbody);
	this->addChild(groundsp);
	groundsp->setTag(0);*/
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
	this->setTouchEnabled(true);
	scheduleUpdate();


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if(m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)  
	{  
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);  
	}
	else
	{
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}  
}
void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	for (auto touch : touches)
	{
		auto location = touch->getLocation();
		addNewSpriteAtPosition(location);
	}
}
void HelloWorld::addNewSpriteAtPosition(Point p)
{
	auto sp = Sprite::create("r_guard.png");
	sp->setTag(1);
	auto body = PhysicsBody::createCircle(15);
	body->getFirstShape()->setDensity(0.01f);
	
	body->setAngularDamping(0.8f);
	body->setLinearDamping(1.2f);
	
	body->applyImpulse(Vec2(2000.f,0.f));
	body->setMass(1.0f);
	body->setContactTestBitmask(0xFFFFFFFF);

	sp->setPhysicsBody(body);
	sp->setPosition(p);
	
	this->addChild(sp);
}
void HelloWorld::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [=](const PhysicsContact& contact)
	{
		CCLog("onContactBegin");
		auto *sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
		int tag = sp->getTag();
		if (tag == 1)
		{
			sp->setTexture("b_guard.png");
			arraysprite->addObject(sp);
	
		}

		sp = (Sprite*)contact.getShapeB()->getBody()->getNode();
		tag = sp->getTag();
		if (tag == 1)
		{
			sp->setTexture("b_guard.png");
	
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener ,10); //第二个参数是优先级，10是随意写的 


}

void HelloWorld::update(float dt)
{
	for (int i=0;i<arraysprite->count(); i++)
	{
		Sprite * sp =(Sprite*) arraysprite->getObjectAtIndex(i);
		sp->getPhysicsBody()->removeFromWorld();
		sp->removeFromParentAndCleanup(true);
		CCLog("update remove");
	}
	arraysprite->removeAllObjects();
}