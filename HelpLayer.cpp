#include "HelpLayer.h"
#include <string>
#include "SimpleAudioEngine.h"
#include "LoadAndSave.h"
using namespace cocos2d;
//初始化布景
bool HelpLayer::init(){
	//调用父类的初始化
	if (!CCLayer::init()){
		return false;
	}
	//开启按键监听
	setKeypadEnabled(true);
	//获取可见区域尺寸
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//获取可见区域原点坐标
	origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//创建主界面的背景
	backGround = CCSprite::create("helpbg.png");
	//设置背景精灵的位置
	
	
	//设置锚点
	backGround->setPosition(visibleSize/2);
	//将添加到布景
	this->addChild(backGround, 0);
	//创建游戏返回按钮
	CCMenuItemSprite* back_menu = CCMenuItemSprite::create
		(
		CCSprite::create("back_menu.png"),
		CCSprite::create("back_menu_select.png"),
		CC_CALLBACK_0(HelpLayer::goToMenuLayer,this)
		);
	//设置按钮位置
	back_menu->setPosition(ccp(origin.x + visibleSize.width - back_menu->getContentSize().width, origin.y + back_menu->getContentSize().height));
	//创建菜单对象
	pMenu = CCMenu::create(back_menu, NULL);
	//设置菜单位置
	pMenu->setPosition(CCPointZero);
	//将菜单添加到布景中
	this->addChild(pMenu, 4);
	//添加返回键监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(HelpLayer::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	this->setEventDispatcher(_eventDispatcher);
	return true;
}
void HelpLayer::goToMenuLayer()
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//返回到菜单界面
	sm->goMenuLayer();

}
void HelpLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		//返回到菜单界面
		sm->goMenuLayer();
	}
}

