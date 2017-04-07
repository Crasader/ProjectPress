//おもちゃの素、おもちゃのクラス定義
//2017/4/7
//GS2 入山奨

#include "Toy.h"

USING_NS_CC;

Toy::Toy()
{
	
}


Toy::~Toy()
{
}

bool Toy::init(int lanenum)
{
	//ファイル名
	std::string filename;

	//画像の種類、場所を決定
	switch (lanenum)
	{
	case 0:
		filename = "box1.png";
		this->setTag(1);
		this->setPosition(Vec2(480 -16- 64, 64));
		break;
	case 1:
		filename = "box2.png";
		this->setTag(2);
		this->setPosition(Vec2(480 - 16 - 32, 64));
		break;
	case 2:
		filename = "box3.png";
		this->setTag(3);
		this->setPosition(Vec2(480 + 16 + 32, 64));
		break;
	case 3:
		filename = "box4.png";
		this->setTag(4);
		this->setPosition(Vec2(480 + 16 + 64, 64));
		break;
	}
	
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	this->Sprite::initWithFile(filename);

	//Sprite::addChild

	//this->setTag()
	
}

Toy* Toy::create(int lanenum)
{
	Toy *toy = new (std::nothrow) Toy();
	if (toy && toy->init(lanenum))
	{
		toy->autorelease();
		return toy;
	}
	CC_SAFE_DELETE(toy);
	return nullptr;
}

void Toy::Shoot()
{
	MoveBy* shot = MoveBy::create(1.0f, Vec2(0.0f, 640.0f));
	this->runAction(shot);
}

void Toy::Change()
{
	//state = 1;
	//ファイル名
	std::string filename;

	//ランダムのおもちゃに決定
	switch (rand() % 4)
	{
	case 0:
		filename = "toy1.png";
		break;
	case 1:
		filename = "toy2.png";
		break;
	case 2:
		filename = "toy3.png";
		break;
	case 3:
		filename = "toy4.png";
		break;
	}

	this->Sprite::initWithFile(filename);

	//タグ情報から色を決定
	switch (this->getTag())
	{
	case 1:
		this->setColor(Color3B(0xff, 0x00, 0x00));
		break;
	case 2:
		this->setColor(Color3B(0x00, 0x00, 0xff));
		break;
	case 3:
		this->setColor(Color3B(0xff, 0xff, 0x00));
		break;
	case 4:
		this->setColor(Color3B(0xff, 0xff, 0x00));
		break;
	}
}

void Toy::OnConveyor()
{
	MoveBy* conveyor = MoveBy::create(3.0f, Vec2(400.0f, 0.0f));
	this->runAction(conveyor);
	create(this->getTag());
}