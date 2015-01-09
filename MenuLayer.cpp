
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include <string.h>
#include "LoadAndSave.h"
#include "MusicLayer.h"
using namespace cocos2d;
//实现MenuLayer类中的init方法，初始化布景
bool MenuLayer::init(){
	//调用父类的初始化
	if (!CCLayer::init()){
		return false;
	}
	//开启返回键监听
	setKeypadEnabled(true);
	//获取可见区域尺寸
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//获取可见区域原点坐标
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//创建背景精灵
	CCSprite* menuBackground = CCSprite::create("gameBackground.png");
	//设置背景精灵的位置
	menuBackground->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//将背景精灵添加到布景
	this->addChild(menuBackground);
	
	//创建开始按钮的精灵
	cocos2d::MenuItemSprite* startgame = MenuItemSprite::create
		(
		Sprite::create("start_game.png"),
		Sprite::create("start_game_select.png"),
		CC_CALLBACK_1(MenuLayer::goToGameLayer,this)
		);
	//创建帮助按钮的精灵
	 cocos2d::MenuItemSprite* help = CCMenuItemSprite::create
		(
		Sprite::create("help.png"),
		Sprite::create("help_select.png"),
		CC_CALLBACK_1(MenuLayer::goToHelpLayer,this)
		);
	//创建声音按钮的精灵
	 cocos2d::MenuItemSprite* soundset = CCMenuItemSprite::create
		(
		Sprite::create("soundset.png"),
		Sprite::create("soundset_select.png"),
		CC_CALLBACK_1(MenuLayer::musicLayer,this)
		);
	//创建退出按钮的精灵
	 cocos2d::MenuItemSprite* exit = MenuItemSprite::create
		(
		Sprite::create("exit_game.png"),
		Sprite::create("exit_game_select.png"),
		CC_CALLBACK_1(MenuLayer::exitGame,this)
		);
	pMenu = CCMenu::create(startgame, help, soundset, exit, NULL);
	//设置菜单位置
	pMenu->setPosition(CCPointZero);
	//设置为菜单不可用
	pMenu->setEnabled(false);
	pMenu->setScale(1.2);
	//将菜单添加到布景中
	this->addChild(pMenu, 4);
	//声明CCNode
	CCNode* child = NULL;
	//获得pMenu中的按钮精灵并存入CCArray
	Vector<Node*>  pArray =  pMenu->getChildren();
	//得到CCArray中元素的数量
	int count = pArray.size();
	//遍历CCArray
	for (int m = 0; m<count; m++)
	{
		//获取menu中的按钮
		child = pArray.at(m);
		//设置按钮的初始位置3
		child->setPosition(ccp(visibleSize.width / 2, 110 * (count - m)));
		child->setOpacity(0);
		child->setCascadeOpacityEnabled(true);
		//创建往上走的动作
		CCActionInterval* moveTo2 = CCSpawn::createWithTwoActions(CCMoveTo::create(1.0f, ccp(visibleSize.width/2, 110 * (count - m)+110)), CCFadeTo::create(0.25f,255));
		//时间延长动作
		CCDelayTime *delay = CCDelayTime::create(0.5 + 0.2f*( m ));
		if (m != 0)
		{
			//创建动作序列
			CCSequence* seq = CCSequence::create(delay, moveTo2, NULL);
			//执行动作
			child->runAction(seq);
		}
		else
		{
			//创建动作序列
			CCSequence* seq0 = CCSequence::create
				(
				delay,
				moveTo2,
				CCCallFuncN::create(this, SEL_CallFuncN(&MenuLayer::setMenuEnabled)),
				NULL
				);
			//在执行动作
			child->runAction(seq0);
		}
	}

	return true;
}
//菜单中按钮执行完动作的回调方法
void MenuLayer::setMenuEnabled(CCObject* pSender)
{
	//设置菜单可用
	pMenu->setEnabled(true);
}
//进入游戏界面
void MenuLayer::goToGameLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	//进入游戏界面
	sm->goGameScene();
}
//退出的回调方法
void MenuLayer::musicLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//关闭返回键监听
	this->setKeypadEnabled(false);
	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	pMenu->setVisible(false);
	//创建半透明层
	MusicLayer *musicLayer = MusicLayer::create();
	//设置半透明层的位置
	musicLayer->setPosition(ccp(0, 0));
	//添加到父类层?
	this->addChild(musicLayer,5);
}
//进入帮助界面
void MenuLayer::goToHelpLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	//进入游戏界面
	sm->goHelpLayer();
}
//退出应用程序
void MenuLayer::exitGame(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	//退出
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		exit(0);
	}
#endif
}
void MenuLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACKSPACE==keycode)
	{

	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	//退出
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		exit(0);
	}
#endif
	}
	
}
