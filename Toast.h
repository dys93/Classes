#include "cocos2d.h"  

USING_NS_CC;

using namespace ui;

class Toast : public LayerColor
{
public:

	static void makeText(Node* node, const std::string& msg, const float& time);//静态函数，方便类直接调用  
	void removeToast(Node* node);
};