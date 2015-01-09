#pragma once
#ifndef __LOADANDSAVE_H__
#define __LOADANDSAVE_H__
#endif
#include "cocos2d.h"
USING_NS_CC;
class LoadAndSave
{

public:
	static void SaveInt(const char* key, int value)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey(key,value);
	}
	static int GetInt(const char* key, int value)
	{
		return CCUserDefault::sharedUserDefault()->getIntegerForKey(key,value);
	}
};

