//おもちゃの素、おもちゃのクラス定義
//2017/4/7
//GS2 入山奨

#include "Toy.h"

USING_NS_CC;

//初期化
//引数 レーン
//戻り値bool
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
		this->setPosition(Vec2(480 + (64 * lanenum) , 64));
		break;
	case 1:
		filename = "box2.png";
		this->setTag(2);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	case 2:
		filename = "box3.png";
		this->setTag(3);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	case 3:
		filename = "box4.png";
		this->setTag(4);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	}
	
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	
}

//生成
//引数 レーン
//戻り値bool
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

//発射
//引数なし
//戻り値なし
void Toy::Shoot()
{
	MoveBy* shot = MoveBy::create(1.0f, Vec2(0.0f, 640.0f));
	this->runAction(shot);
}

//画像変更
//引数なし
//戻り値なし
bool Toy::Change()
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

	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

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

//コンベアの上に乗ったときの処理
//引数なし
//戻り値なし
void Toy::OnConveyor()
{
	//移動
	MoveBy* conveyor = MoveBy::create(3.0f, Vec2(0.0f, 1000.0f));
	this->runAction(conveyor);

	//作り直す
	//this->addChild(create(this->getTag()));
	int tag = this->getTag() - 1;

	//Toy* toy = Toy::create(tag);
	
	//getParent()->addChild(toy);

	//this->removeFromParentAndCleanup(true);

	//return toy;
}

void Toy::Failed()
{
	this->setTag(0);
}