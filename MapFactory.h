#pragma once
#include "cocos2d.h"
#include <vector>
#include "GameScene.h"
using namespace std;
USING_NS_CC;
class MapFactory
{
private:
	
public:
	MapFactory();
	~MapFactory();
	void getMap(int mapnum);
	void clear();
	void createobject(int b,int k,float x,float y);
	void MapLoad(GameScene *target);
	int Mapnum;
	int initmoney;
	int earn;
	vector <int> belonglist;
	vector<int>	kindlist;
	vector<float> xlist;
	vector<float> ylist;
};

