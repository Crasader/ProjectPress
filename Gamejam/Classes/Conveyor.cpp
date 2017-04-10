//�R���x�A�̃N���X��`
//2017/4/10
//GS2 ���R��

#include "Conveyor.h"

USING_NS_CC;

//������
//���� ���[��
//�߂�lbool
bool Conveyor::init(int lanenum)
{
	//�t�@�C����
	std::string filename;

	filename = "conveyor.png";

	//�摜�̎�ށA�ꏊ������
	switch (lanenum)
	{
	case 0:
		this->setTag(1);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 1:
		this->setTag(2);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 2:
		this->setTag(3);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 3:
		this->setTag(4);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	}

	this->setScale(2.0f);

	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

}

//���[������
//���� ���[��
//�߂�l Conveyor*
Conveyor* Conveyor::create(int lanenum)
{
	Conveyor *conveyor = new (std::nothrow) Conveyor();
	if (conveyor && conveyor->init(lanenum))
	{
		conveyor->autorelease();
		return conveyor;
	}
	CC_SAFE_DELETE(conveyor);
	return nullptr;
}

Toy* Conveyor::Spawn(int lanenum)
{
	bool check = true;

	//�t�@�C����
	std::string filename;

	//�摜�̎�ށA�ꏊ������
	switch (lanenum)
	{
	case 0:
		filename = "box1.png";
		this->setTag(1);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 1:
		filename = "box2.png";
		this->setTag(2);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 2:
		filename = "box3.png";
		this->setTag(3);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	case 3:
		filename = "box4.png";
		this->setTag(4);
		this->setPosition(Vec2(480 + (64 * lanenum), 0));
		break;
	}

	if (!Sprite::initWithFile(filename))
	{
		check = false;
	}


	Toy *toy = new (std::nothrow) Toy();
	if (toy && check)
	{
		toy->autorelease();
		return toy;
	}
	CC_SAFE_DELETE(toy);
	return nullptr;


}

