#include "cocos2d.h"  

USING_NS_CC;

using namespace ui;

class Toast : public LayerColor
{
public:

	static void makeText(Node* node, const std::string& msg, const float& time);//��̬������������ֱ�ӵ���  
	void removeToast(Node* node);
};