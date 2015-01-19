#include "Toast.h"  
#include "infor.h"
void Toast::makeText(cocos2d::Node *node, const std::string &msg, const float &time)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pLabel = Label::createWithSystemFont(msg, "Arial", 30);
	pLabel->setColor(Color3B::WHITE);
	pLabel->ignoreAnchorPointForPosition(false);
	pLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto ly = LayerColor::create(Color4B(130, 120, 120, 255));
	ly->ignoreAnchorPointForPosition(false);
	ly->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ly->setContentSize(pLabel->getContentSize() + Size(20, 15));
	pLabel->setZOrder(PrioGame::Toast);
	node->addChild(ly);
	node->addChild(pLabel);
	ly->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - pLabel->getContentSize().height));
	pLabel->setPosition(ly->getPosition());
	auto seq1 = Sequence::create(FadeIn::create(time / 5), DelayTime::create(time / 5 * 1.5), FadeOut::create(time / 5 * 2.5), CallFuncN::create(ly, callfuncN_selector(Toast::removeToast)), nullptr);
	auto seq2 = Sequence::create(DelayTime::create(time / 5 * 3), nullptr);
	auto spawn = Spawn::create(seq1, seq2, nullptr);
	auto action = Repeat::create(spawn, 1);
	ly->setOpacity(0);
	
	pLabel->setOpacity(0);
	
	pLabel->setZOrder(100);
	ly->runAction(action);
	pLabel->runAction(action->clone());
}

void Toast::removeToast(Node* node)
{
	log("node = %s", node->getDescription().c_str());
	this->removeFromParentAndCleanup(true);
}