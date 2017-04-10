//おもちゃの素、おもちゃのクラス宣言
//2017/4/7
//GS2 入山奨

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);

public:
	static Toy* create(int lanenum);
	void Shoot();
	bool Change();
	void OnConveyor();
	void Failed();
};

