
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include <string.h>
#include "LoadAndSave.h"
#include "MusicLayer.h"
using namespace cocos2d;
//ʵ��MenuLayer���е�init��������ʼ������
bool MenuLayer::init(){
	//���ø���ĳ�ʼ��
	if (!CCLayer::init()){
		return false;
	}
	//�������ؼ�����
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
	
	//������ʼ��ť�ľ���
	cocos2d::MenuItemSprite* startgame = MenuItemSprite::create
		(
		Sprite::create("start_game.png"),
		Sprite::create("start_game_select.png"),
		CC_CALLBACK_1(MenuLayer::goToGameLayer,this)
		);
	//����������ť�ľ���
	 cocos2d::MenuItemSprite* help = CCMenuItemSprite::create
		(
		Sprite::create("help.png"),
		Sprite::create("help_select.png"),
		CC_CALLBACK_1(MenuLayer::goToHelpLayer,this)
		);
	//����������ť�ľ���
	 cocos2d::MenuItemSprite* soundset = CCMenuItemSprite::create
		(
		Sprite::create("soundset.png"),
		Sprite::create("soundset_select.png"),
		CC_CALLBACK_1(MenuLayer::musicLayer,this)
		);
	//�����˳���ť�ľ���
	 cocos2d::MenuItemSprite* exit = MenuItemSprite::create
		(
		Sprite::create("exit_game.png"),
		Sprite::create("exit_game_select.png"),
		CC_CALLBACK_1(MenuLayer::exitGame,this)
		);
	pMenu = CCMenu::create(startgame, help, soundset, exit, NULL);
	//���ò˵�λ��
	pMenu->setPosition(CCPointZero);
	//����Ϊ�˵�������
	pMenu->setEnabled(false);
	pMenu->setScale(1.2);
	//���˵���ӵ�������
	this->addChild(pMenu, 4);
	//����CCNode
	CCNode* child = NULL;
	//���pMenu�еİ�ť���鲢����CCArray
	Vector<Node*>  pArray =  pMenu->getChildren();
	//�õ�CCArray��Ԫ�ص�����
	int count = pArray.size();
	//����CCArray
	for (int m = 0; m<count; m++)
	{
		//��ȡmenu�еİ�ť
		child = pArray.at(m);
		//���ð�ť�ĳ�ʼλ��3
		child->setPosition(ccp(visibleSize.width / 2, 110 * (count - m)));
		child->setOpacity(0);
		child->setCascadeOpacityEnabled(true);
		//���������ߵĶ���
		CCActionInterval* moveTo2 = CCSpawn::createWithTwoActions(CCMoveTo::create(1.0f, ccp(visibleSize.width/2, 110 * (count - m)+110)), CCFadeTo::create(0.25f,255));
		//ʱ���ӳ�����
		CCDelayTime *delay = CCDelayTime::create(0.5 + 0.2f*( m ));
		if (m != 0)
		{
			//������������
			CCSequence* seq = CCSequence::create(delay, moveTo2, NULL);
			//ִ�ж���
			child->runAction(seq);
		}
		else
		{
			//������������
			CCSequence* seq0 = CCSequence::create
				(
				delay,
				moveTo2,
				CCCallFuncN::create(this, SEL_CallFuncN(&MenuLayer::setMenuEnabled)),
				NULL
				);
			//��ִ�ж���
			child->runAction(seq0);
		}
	}

	return true;
}
//�˵��а�ťִ���궯���Ļص�����
void MenuLayer::setMenuEnabled(CCObject* pSender)
{
	//���ò˵�����
	pMenu->setEnabled(true);
}
//������Ϸ����
void MenuLayer::goToGameLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	//������Ϸ����
	sm->goGameScene();
}
//�˳��Ļص�����
void MenuLayer::musicLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//�رշ��ؼ�����
	this->setKeypadEnabled(false);
	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	pMenu->setVisible(false);
	//������͸����
	MusicLayer *musicLayer = MusicLayer::create();
	//���ð�͸�����λ��
	musicLayer->setPosition(ccp(0, 0));
	//��ӵ������?
	this->addChild(musicLayer,5);
}
//�����������
void MenuLayer::goToHelpLayer(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	//������Ϸ����
	sm->goHelpLayer();
}
//�˳�Ӧ�ó���
void MenuLayer::exitGame(CCObject* pSender)
{
	if (LoadAndSave::GetInt("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	//�˳�
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

	//���ò˵���ť�Ŀ�����
	pMenu->setEnabled(false);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	//�˳�
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		exit(0);
	}
#endif
	}
	
}
