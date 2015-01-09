#include "SpriteFactory.h"
#include<String>


using namespace std;
USING_NS_CC;



MySprite* MySprite::creates(int belongto,int kind )
{
	//初始化数据
	MySprite *wait = new MySprite();
	string a = sprite_pic[belongto * 5 + kind] + ".png";
	if (wait->initWithFile(sprite_pic[belongto * 5 + kind] + ".png"))
	{
		wait->sleep = CCSprite::create(sprite_pic_sleep[belongto]+".png");

		wait->sleep->setVisible(false);
		wait->sleep->setScale(0.6);
		wait->sleep->setPosition(wait->getContentSize());
		wait->setGlobalZOrder(PrioGame::SpriteSleep);
		wait->addChild(wait->sleep);
		
		//自身的数据设定
		wait->setTag(belongto * 100 + kind * 10);
		wait->ismenushow = false;
		wait->setScale(sprite_scale[belongto * 5 + kind]);
		wait->setRotation(sprite_rotation[belongto * 5 + kind] * 180);
		wait->menu =  CCArray::create();
		wait->menu->retain();
		wait->hasattck =true;
		wait->Maxmove = sprite_max_move[kind];
		wait->hasmove = sprite_max_move[kind];
		wait->Maxspeed = sprite_max_speed[kind] * speed;
		wait->setAnchorPoint(ccp( 0,0));
		wait->kind = kind;
		wait->belongto = belongto;
		wait->hurt = false;
		wait->Maxblood = sprite_max_blood[kind];
		wait->sleeptime = 1;
		wait->menunum = sprite_menu_num[kind];
		wait->hurt = false;
		
		wait->setOpacity(opac);

		//设定战争阴影效果
		if (UserDefault::sharedUserDefault()->getBoolForKey("openshade"), 1)
		{
			wait->breakshade = CCSprite::create("break_shade.png");
			wait->breakshade->setScale(sprite_break_shade[kind]);
			wait->breakshade->setBlendFunc(ccBlendFunc{ GL_DST_COLOR, GL_ZERO });
		}
		//物理体积设定
		PhysicsBody* body;
		if (kind == 3)
		{
			body = PhysicsBody::createBox
				(CCSizeMake(1.1*sprite_sizex[kind], 1.1*sprite_sizey[kind]));
			body->setDynamic(false);
			body->setMass(0);
		}
		else if (kind == 4)
		{
			body = PhysicsBody::createCircle(0.9*sprite_sizex[kind]);

		}
		else
		{
			body = PhysicsBody::createBox
				(Size(1.7*sprite_sizex[kind], 1.7*sprite_sizey[kind]));
			
		}
		body->getFirstShape()->setDensity(density);

		body->setAngularDamping(angulardamping);
		body->setLinearDamping(lineardamping);

		body->setMass(1.0f);
		body->setContactTestBitmask(0xFFFFFFFF);
		body->setCollisionBitmask(0xFFFFFFFF);
		body->setCategoryBitmask(0xFFFFFFFF);
		wait->setPhysicsBody(body);
		//菜单选项设定
		wait->createmenu();
		wait->nosel(GameState::g_begin);
		wait->trysleep();
		wait->addspeed(Vec2(0,1));
		return wait;

	}
	CC_SAFE_DELETE(wait);//清除资源
	return NULL;
}
//显示精灵的选择菜单
void MySprite::showmenu()
{
	if (ismenushow == true)
		return;
	ismenushow = true;
	for (int i = 0; i < menu->count(); i++)
	{
		if (i == 1 && UserDefault::sharedUserDefault()->getBoolForKey("limit", true) == true && kind != 3 )
		{
			continue;
		}
		else{
		//	double  aaa = sprite_menu_position_x[belongto * 5 + kind] * sprite_menu_x[i] + this->getPosition().x;
			Sprite * sp = (Sprite*)menu->getObjectAtIndex(i);
			sp->setPosition(Vec2(
				sprite_menu_position_x[belongto * 5 + kind] * sprite_menu_x[i] ,
				sprite_menu_position_y[belongto * 5 + kind] * sprite_menu_y[i] ));
			sp->setVisible(true);
			sp->setOpacity(255);
		}
		
	}
}
//隐藏精灵的选择菜单
void MySprite::hidemenu()
{
	if (ismenushow == false)
		return;
	ismenushow = false;
	for (int i = 0; i < menu->count(); i++)
	{
			if (i == 1 && UserDefault::sharedUserDefault()->getBoolForKey("limit", true) == true && kind != 3)
			{
				continue;
			}
			Sprite * sp = (Sprite*)menu->getObjectAtIndex(i);
			sp->setVisible(0);
		}
	
}
//给精灵一个方向上的速度
void MySprite::addspeed(Vec2 speed)
{
	hasmove++;
	if (speed.getDistance(CCPointZero) > this->Maxspeed)
		this->getPhysicsBody()->applyImpulse(1.5*this->Maxspeed / speed.getDistance(CCPointZero)*speed);
	else
	{
		this->getPhysicsBody()->applyImpulse(1.5*speed);
	}
}

void MySprite::createmenu()
{
	for (int i = 0; i < sprite_menu_num[i] && kind != 4 && kind != 9; i++)
	{
		CCSprite *ccsp;
		if (kind == 3 )
		{
			ccsp = CCSprite::create(
				sprite_pic[ kind] + "_menu_" + char('0' + i) + ".png");
			
			ccsp->setScale(0.8);
		}
		else
		{
			ccsp = CCSprite::create(string("sprite_menu_") + char('0' + i) + ".png");
			ccsp->setScale(1);
		}
		menu->addObject(ccsp);
		ccsp->setAnchorPoint(CCPointZero);
		ccsp->setPosition(ccp(
			sprite_menu_position_x[belongto * 5 + kind] * sprite_menu_x[i],
			sprite_menu_position_y[belongto * 5 + kind] * sprite_menu_y[i]));
		ccsp->setVisible(false);
		
		ccsp->setTag(belongto*100+kind*10+i);
		ccsp->setGlobalZOrder(PrioGame::SpriteMenu);
		this->addChild(ccsp);
	}

}
//血量不足 死亡 返回true
bool MySprite::trydie()
{
	if (hurt)
	{
		Maxblood--;
		hurt = false;
	}
	if (Maxblood == 0&&(this->getPhysicsBody()->getVelocity()).getDistance(CCSizeZero)<10.0)
	{
		this->removeFromParent();
		this->getPhysicsBody()->removeFromWorld();
		die_animation();
		this->removeFromParentAndCleanup(true);

		return true;
	}
	return false;
}
//死亡动画
CCParticleSystem * MySprite::die_animation()
{
	CCParticleSystem *particle = NULL;
	particle = CCParticleExplosion::create();
	particle->retain();
	particle->setTexture(CCTextureCache::sharedTextureCache()
		->addImage("star.png"));
	
	particle->setDuration(0.15);
	particle->setEmissionRate(200);

	particle->setSpeed(40);
	particle->setSpeedVar(5);
	
	particle->setStartSize(8);
	particle->setStartSizeVar(2);

	particle->setLife(0.8);
	particle->setLifeVar(0.5);

	particle->setEndSize(7);
	particle->setEndSizeVar(2);
	if (belongto == 0){
		particle->setStartColor(Color4F(0.1, 0.9, 0.9, 0.9));
		particle->setStartColorVar(Color4F(0.1, 0.1, 0.1, 0.1));

		particle->setEndColor(Color4F(0.9, 0.9, 0.9, 0.0));
		particle->setEndColorVar(Color4F(0.1, 0.1, 0.1, 0.0));
	}
	else
	{
		particle->setStartColor(Color4F(0.1, 0.1, 0.9, 0.9));
		particle->setStartColorVar(Color4F(0.1, 0.1, 0.1, 0.1));

		particle->setEndColor(Color4F(0.9, 0.9, 0.9, 0.0));
		particle->setEndColorVar(Color4F(0.1, 0.1, 0.1, 0.0));
	}

	particle->setAutoRemoveOnFinish(true);
	return particle;
}

void MySprite::dayup()
{

	if (sleeptime > 0)
	{
		sleeptime--;
	}
	if (sleeptime == 0)
	{
		getup_animation();
		hasmove = 0;
		hasattck = 0;
	}
}
void MySprite::getup_animation()
{
	this->sleep->setVisible(false);
}
//攻击函数
MySprite* MySprite::attack(Vec2 speed)
{
	if (kind != 3){
		this->hidemenu();
		this->hasattck = true;
		this->hasmove++;
		if (kind != 2)
		{
			this->addspeed(speed);
			return NULL;
		}
		//蛇的攻击方法
		else if (kind == 2)
		{

			Vec2 mm = this->getPosition() + speed / speed.distance(CCSizeZero)*10;
			MySprite *array = MySprite::creates( belongto,4);
			array->setPosition(mm);
			//选择一定角度
			float rotateRadians = speed.getAngle();
			float rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
			array->setRotation(rotateDegrees);
			array->attack(speed);
			array->setScale(0.25);
			array->setGlobalZOrder(PrioGame::Sprite);
			this->addChild(array);
			return array;
		}
	}

}

void MySprite::besel(GameState state)
{
	//判断是否可以被选定
	if (sleeptime > 0||hasmove==Maxmove||hasattck)
	{
		return;
	}
	showmenu();
	if (state == g_move1&&kind == 2)
	{
		auto ccsp = (CCSprite*)menu->objectAtIndex(2);
		ccsp->setVisible(false);
	}
	this->setOpacity(200);
}

void MySprite::nosel(GameState state)
{
	hidemenu();
	this->setOpacity(255);
}
bool MySprite::trysleep()
{
	
	if ((hasmove || hasattck)&&this->kind != 4)
	{
		if (sleeptime==0)
		sleeptime=1;
		if (belongto==0)
		sleep_animation();
		return true;
	}
	return false;
}

void MySprite::sleep_animation()
{
	this->sleep->setVisible(true);
}

//
void MySprite::behurt()
{
	if (hurt == false)
	{
		hurt = true;
		CCParticleSystem *particle = NULL;
		particle = CCParticleExplosion::create();
		particle->retain();
		particle->setTexture(CCTextureCache::sharedTextureCache()
			->addImage("star.png"));

		particle->setDuration(0.4);
		particle->setEmissionRate(200);

		particle->setSpeed(40);
		particle->setSpeedVar(5);

		particle->setStartSize(12);
		particle->setStartSizeVar(2);

		particle->setLife(1.0);
		particle->setLifeVar(0.5);

		particle->setEndSize(10);
		particle->setEndSizeVar(2);
		if (belongto == 0){
			particle->setStartColor(Color4F(0.05, 0.05, 0.05, 0.95));
			particle->setStartColorVar(Color4F(0.05, 0.05, 0.05, 0.05));

			particle->setEndColor(Color4F(0.95, 0.95, 0.95, 0.0));
			particle->setEndColorVar(Color4F(0.05, 0.05, 0.05, 0.0));

		}
		else
		{
			particle->setStartColor(Color4F(0.95, 0.95, 0.95, 0.95));
			particle->setStartColorVar(Color4F(0.05, 0.05, 0.05, 0.05));

			particle->setEndColor(Color4F(0.95, 0.95, 0.95, 0.0));
			particle->setEndColorVar(Color4F(0.05, 0.05, 0.05, 0.0));
		}
		particle->setPosition(this->getPosition()/10);
		particle->setAutoRemoveOnFinish(true);
		particle->setGlobalZOrder(PrioGame::SpriteDiePar);
		this->addChild(particle);


	}

}