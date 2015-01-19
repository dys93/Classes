
#include "MusicLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "LoadAndSave.h"

USING_NS_CC;

bool MusicLayer::init(){
	//��������
	bool bRet = false;
	do
	{
		//CC_BREAK_IF(!CCLayerGradient::initWithColor(ccc4(250, 250, 250, 0), ccc4(0, 0, 0, 0), ccp(0, 1)));
		//����initDialog����
		this->initDialog();

		//ע�����
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
	//��ȡ�ɼ�����ߴ�
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//������������
	CCSprite* menuBackground = CCSprite::create("gameBackground.png");
	//���ñ��������λ��
	menuBackground->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//������������ӵ�����
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
	//������Ϸ���ذ�ť
	cocos2d::MenuItemSprite* back_menu = MenuItemSprite::create
		(
		Sprite::create("back_menu.png"),
		Sprite::create("back_menu_select.png"),
		CC_CALLBACK_1(MusicLayer::menuCallbacKToMenuLayer,this)
		);
	//���ð�ťλ��
	back_menu->setPosition(ccp(visibleSize.width * 4 / 11, visibleSize.height * 2 / 11));
	pMenu = CCMenu::create(soundon, soundclose, effecton, effectclose, back_menu, NULL);
	////���ò˵�λ��
	pMenu->setPosition(CCPointZero);
	//����Ϊ�˵�������
	pMenu->setEnabled(false);
	pMenu->setScale(1.1);
	//���˵���ӵ�������
	this->addChild(pMenu, 9);
	//��ɫ��ִ�ж���
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
	//���ò˵�Ϊ����
	pMenu->setEnabled(true);
	pMenu->setVisible(true);
}
void MusicLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		this->setKeypadEnabled(false);
		//���ò˵���ť�Ŀ�����
		pMenu->setEnabled(false);
		//��ɫ��ִ�ж���

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
	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	//��ɫ��ִ�ж���
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
	//��ȡ���ఴť�������
	MenuLayer* menuLayer = (MenuLayer*)this->getParent();
	//���ð�ť����
	menuLayer->pMenu->setEnabled(true);
	menuLayer->pMenu->setCascadeOpacityEnabled(true);
	menuLayer->pMenu->setOpacity(0);
	menuLayer->pMenu->setVisible(true);
	menuLayer->pMenu->runAction(CCFadeTo::create(1, 255));
	//�迪������㷵�ؼ�����
	menuLayer->setKeypadEnabled(true);
	//�Ӹ������Ƴ��ò�
	this->removeFromParentAndCleanup(false);

}
//������
void  MusicLayer::menuCallbacKOpenMusic(CCObject* pSender)
{

	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//preferencecaoz����
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic
		(
		"sound/background.wav",
		true
		);
	LoadAndSave::SaveInt("musicFlag", 1);
	soundon->setVisible(false);
	soundclose->setVisible(true);


}
//�ر�����
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
//����Ч
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
//�ر���Ч
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
