//コンベアのクラス宣言
//2017/4/10
//GS2 入山奨

#include "cocos2d.h"
#include "Toy.h"

#pragma once
class Conveyor:public cocos2d::Sprite
{
private:
	bool init(int lanenum);
	bool initToy(int lanenum);

public:
	static Conveyor* create(int lanenum);
	Toy* Spawn(int lanenum);
};

