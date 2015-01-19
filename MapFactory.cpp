#include "MapFactory.h"


MapFactory::MapFactory()
{
}


MapFactory::~MapFactory()
{
}
void MapFactory::clear()
{
	belonglist.clear();
	kindlist.clear();
	xlist.clear();
	ylist.clear();
}
void MapFactory::createobject(int b, int k, float x, float y)
{
	belonglist.push_back(b);
	kindlist.push_back(k);
	xlist.push_back(x);
	ylist.push_back(y);
}
void MapFactory::getMap(int mapnum)
{
	clear();
	this->Mapnum = mapnum;
	initmoney=300;
	earn=100;
	
	switch (mapnum)
	{
	case 0:{//normal
		createobject(1, 3, 0.5, 6.0/7 );
		createobject(1, 2, 0.5, 6.0 / 7-1.0/10);
		createobject(1, 1, 0.5 ,6.0 / 7 - 2.0 / 10);
		createobject(1, 0, 0.5, 6.0 / 7 - 3.0 / 10);

		createobject(0, 0, 0.5,1.0 / 7 + 3.0 / 10);
		createobject(0, 1, 0.5, 1.0 / 7 + 2.0 / 10);
		createobject(0, 2, 0.5, 1.0 / 7 + 1.0 / 10);
		createobject(0, 3, 0.5,1.0 / 7);
	}
		break;
	case 1:{//正面冲突
		createobject(1, 0, 0.5, 6.0 / 7);
		createobject(1, 1, 0.5, 6.0 / 7 - 1.0 / 10);
		createobject(1, 2, 0.5, 6.0 / 7 - 2.0 / 10);
		createobject(1, 3, 0.8, 6.0 / 7 - 3.0 / 10);

		createobject(0, 3, 0.2, 1.0 / 7 + 3.0 / 10);
		createobject(0, 2, 0.5, 1.0 / 7 + 2.0 / 10);
		createobject(0, 1, 0.5, 1.0 / 7 + 1.0 / 10);
		createobject(0, 0, 0.5, 1.0 / 7);
	}
		break;
	case 2:{//巨富
		initmoney = 500;
		createobject(1, 3, 0.5, 6.0 / 7);
		createobject(1, 2, 0.5, 6.0 / 7 - 1.0 / 10);
		createobject(1, 1, 0.5, 6.0 / 7 - 2.0 / 10);
		createobject(1, 0, 0.5, 6.0 / 7 - 3.0 / 10);

		createobject(0, 3, 0.5, 1.0 / 7);
	}
		break;
	case 3:{//一股作气
		initmoney = 500;
		createobject(1, 3, 0.5, 6.0 / 7);
		createobject(1, 0, 0.5, 6.0 / 7 - 1.0 / 10);
		createobject(1, 0, 0.5, 6.0 / 7 - 2.0 / 10);


		createobject(0, 1, 0.3, 1.0 / 7 + 2.0 / 10);
		createobject(0, 1, 0.3, 1.0 / 7 + 1.0 / 10);
		createobject(0, 1, 0.7, 1.0 / 7 + 2.0 / 10);
		createobject(0, 1, 0.7, 1.0 / 7 + 1.0 / 10);

	}
		break;
	case 4:{  //防御
		createobject(1, 3, 0.5, 6.0 / 7);
		createobject(1, 2, 0.5, 6.0 / 7 - 1.0 / 10);
		createobject(1, 1, 0.5, 6.0 / 7 - 2.0 / 10);
		createobject(1, 0, 0.5, 6.0 / 7 - 3.0 / 10);

		for (int i = 1; i <= 9;i++)
			createobject(2, 0, i/10.0, 0.5);

		createobject(0, 0, 0.5, 1.0 / 7 + 3.0 / 10);
		createobject(0, 1, 0.5, 1.0 / 7 + 2.0 / 10);
		createobject(0, 2, 0.5, 1.0 / 7 + 1.0 / 10);
		createobject(0, 3, 0.5, 1.0 / 7);
		}
		break;
	case 5:{//入侵
		createobject(1, 3, 0.5, 6.0 / 7);
		createobject(0, 2, 0.5, 6.0 / 7 - 1.0 / 10);
		createobject(0, 1, 0.5, 6.0 / 7 - 2.0 / 10);
		createobject(0, 0, 0.5, 6.0 / 7 - 3.0 / 10);

		for (int i = 1; i <= 9; i++)
			createobject(2, 0, i / 10.0, 0.5);

		createobject(1, 0, 0.5, 1.0 / 7 + 3.0 / 10);
		createobject(1, 1, 0.5, 1.0 / 7 + 2.0 / 10);
		createobject(1, 2, 0.5, 1.0 / 7 + 1.0 / 10);
		createobject(0, 3, 0.5, 1.0 / 7);
	}
		break;
	}
}

void MapFactory::MapLoad(GameScene *target)
{
	target->money = this->initmoney;
	target->earn = this->earn;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < kindlist.size(); i++)
	{
		int xp = 1.0 / 9 * visibleSize.width + xlist[i] * visibleSize.width*7.0/9;
		int yp = 1.0 / 9 * visibleSize.height + ylist[i] * visibleSize.height*7.0 / 9;
		target->create_ani(belonglist[i],kindlist[i],CCSizeMake(xp,yp));
	}
	
}

