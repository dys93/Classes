#include "HelpLayer.h"
#include <string>
#include "SimpleAudioEngine.h"
#include "LoadAndSave.h"
using namespace cocos2d;
//��ʼ������
bool HelpLayer::init(){
	//���ø���ĳ�ʼ��
	if (!CCLayer::init()){
		return false;
	}
	//������������
	setKeypadEnabled(true);
	//��ȡ�ɼ�����ߴ�
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//��ȡ�ɼ�����ԭ������
	origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//����������ı���
	backGround = CCSprite::create("helpbg.png");
	//���ñ��������λ��
	
	
	//����ê��
	backGround->setPosition(visibleSize/2);
	//����ӵ�����
	this->addChild(backGround, 0);
	//������Ϸ���ذ�ť
	CCMenuItemSprite* back_menu = CCMenuItemSprite::create
		(
		CCSprite::create("back_menu.png"),
		CCSprite::create("back_menu_select.png"),
		CC_CALLBACK_0(HelpLayer::goToMenuLayer,this)
		);
	//���ð�ťλ��
	back_menu->setPosition(ccp(origin.x + visibleSize.width - back_menu->getContentSize().width, origin.y + back_menu->getContentSize().height));
	//�����˵�����
	pMenu = CCMenu::create(back_menu, NULL);
	//���ò˵�λ��
	pMenu->setPosition(CCPointZero);
	//���˵���ӵ�������
	this->addChild(pMenu, 4);
	//��ӷ��ؼ�����
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
	//���ص��˵�����
	sm->goMenuLayer();

}
void HelpLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		//���ص��˵�����
		sm->goMenuLayer();
	}
}

