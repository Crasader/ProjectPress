//��������̑f�A��������̃N���X�錾
//2017/4/7
//GS2 ���R��

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);
	static Toy* create(int lanenum);
	bool state;
	

public:
	Toy();
	~Toy();
	void Shoot();
	void Change();
	void OnConveyor();
};

