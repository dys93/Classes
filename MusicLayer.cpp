
#include "MusicLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "LoadAndSave.h"

USING_NS_CC;

bool MusicLayer::init(){
	//返回类型
	bool bRet = false;
	do
	{
		//CC_BREAK_IF(!CCLayerGradient::initWithColor(ccc4(250, 250, 250, 0), ccc4(0, 0, 0, 0), ccp(0, 1)));
		//条用initDialog方法
		this->initDialog();

		//注册监听
		auto listenerkeyPad = EventListenerKeyboard::create();
		listenerkeyPad->onKeyReleased = CC_CALLBACK_2(MusicLayer::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

		this->setEventDispatcher(_eventDispatcher);
		bRet = true;
	} while (0);


	return bRet;
}
void MusicLayer::initDialog(){

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

	soundon = MenuItemSprite::create
		(
		Sprite::create("open_music.png"),
		Sprite::create("open_music_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbacKOpenMusic,this)
		);
	soundon->setPosition(ccp(visibleSize.width *7/11, visibleSize.height *6/11));
	soundclose = MenuItemSprite::create
		(
		Sprite::create("close_music.png"),
		Sprite::create("close_music_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbackCloseMusic,this)
		);
	soundclose->setPosition(ccp(visibleSize.width *7/11, visibleSize.height *6/11));
	if ( LoadAndSave::GetInt("musicFlag", 1) == 1)
	{
		soundon->setVisible(false);
		soundclose->setVisible(true);
	}
	else
	{
		soundon->setVisible(true);
		soundclose->setVisible(false);
	}
	effecton = CCMenuItemSprite::create
		(
		Sprite::create("open_effect.png"),
		Sprite::create("open_effect_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbackOpengEffect,this)
		);
	effecton->setPosition(ccp(visibleSize.width *7/11, visibleSize.height *4/11));
	effectclose = CCMenuItemSprite::create
		(
		Sprite::create("close_effect.png"),
		Sprite::create("close_effect_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbackCloseEffect,this)
		);
	effectclose->setPosition(ccp(visibleSize.width * 7 / 11, visibleSize.height * 4 / 11));
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		effecton->setVisible(false);
		effectclose->setVisible(true);

	}
	else
	{
		effecton->setVisible(true);
		effectclose->setVisible(false);
	}
	//创建游戏返回按钮
	cocos2d::MenuItemSprite* back_menu = MenuItemSprite::create
		(
		Sprite::create("back_menu.png"),
		Sprite::create("back_menu_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbacKToMenuLayer,this)
		);
	//设置按钮位置
	back_menu->setPosition(ccp(visibleSize.width * 4 / 11, visibleSize.height * 2 / 11));
	pMenu = CCMenu::create(soundon, soundclose, effecton, effectclose, back_menu, NULL);
	////设置菜单位置
	pMenu->setPosition(CCPointZero);
	//设置为菜单不可用
	pMenu->setEnabled(false);
	pMenu->setScale(1.1);
	//将菜单添加到布景中
	this->addChild(pMenu, 9);
	//颜色层执行动作
	this->setCascadeOpacityEnabled(true);
	this->setOpacity(0);
	this->runAction
		(
		CCSequence::create
		(
		CCSpawn::createWithTwoActions(CCMoveTo::create(1, Vec2(1000, 0))->reverse(), CCFadeTo::create(1,255)),
		CCCallFunc::create(CC_CALLBACK_0(MusicLayer::resumeMenu,this)),
		NULL
		)
	);
}


void MusicLayer::resumeMenu()
{
	//设置菜单为可用
	pMenu->setEnabled(true);
	pMenu->setVisible(true);
}
void MusicLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		this->setKeypadEnabled(false);
		//设置菜单按钮的可用性
		pMenu->setEnabled(false);
		//颜色层执行动作

		this->setCascadeOpacityEnabled(true);
		this->runAction
			(
			CCSequence::create
			(
			CCSpawn::createWithTwoActions(CCMoveTo::create(1, Vec2(1000, 0)), CCFadeOut::create(1)),
			CCCallFuncN::create( CC_CALLBACK_1(MusicLayer::menuCallbackKeyBackClicked,this)),
			NULL
			)
			);
	}
}
void MusicLayer::menuCallbacKToMenuLayer(CCObject* pSender)
{

	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	this->setKeypadEnabled(false);
	//设置菜单按钮的可用性
	pMenu->setEnabled(false);
	//颜色层执行动作
	this->setCascadeOpacityEnabled(true);
	this->setCascadeColorEnabled(true);
	this->runAction
		(
		CCSequence::create
		(
		CCSpawn::create(CCMoveTo::create(1, Vec2(1000, 0)), CCFadeOut::create(1),CCCallFuncN::create(CC_CALLBACK_1(MusicLayer::menuCallbackKeyBackClicked, this)), NULL),
		
		NULL
		)
		);
}
void MusicLayer::menuCallbackKeyBackClicked(CCObject* pSender)
{
	//获取父类按钮层的引用
	MenuLayer* menuLayer = (MenuLayer*)this->getParent();
	//设置按钮可用
	menuLayer->pMenu->setEnabled(true);
	menuLayer->pMenu->setCascadeOpacityEnabled(true);
	menuLayer->pMenu->setOpacity(0);
	menuLayer->pMenu->setVisible(true);
	menuLayer->pMenu->runAction(CCFadeTo::create(1, 255));
	//设开启父类层返回键监听
	menuLayer->setKeypadEnabled(true);
	//从父类中移除该层
	this->removeFromParentAndCleanup(false);

}
//打开声音
void  MusicLayer::menuCallbacKOpenMusic(CCObject* pSender)
{

	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//preferencecaoz操作
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic
		(
		"sound/background.wav",
		true
		);
	LoadAndSave::SaveInt("musicFlag", 1);
	soundon->setVisible(false);
	soundclose->setVisible(true);


}
//关闭声音
void  MusicLayer::menuCallbackCloseMusic(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	LoadAndSave::SaveInt("musicFlag", 0);
	soundon->setVisible(true);
	soundclose->setVisible(false);
}
//打开音效
void  MusicLayer::menuCallbackOpengEffect(CCObject* pSender)
{
	LoadAndSave::SaveInt("effectFlag", 1);
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	effecton->setVisible(false);
	effectclose->setVisible(true);
}
//关闭音效
void  MusicLayer::menuCallbackCloseEffect(CCObject* pSender)
{
	LoadAndSave::SaveInt("effectFlag", 0);
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	effecton->setVisible(true);
	effectclose->setVisible(false);
}
