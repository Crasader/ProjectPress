//おもちゃの素、おもちゃのクラス定義
//2017/4/7
//GS2 入山奨

#include "Toy.h"

USING_NS_CC;



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

//初期化
//引数 レーン
//戻り値bool
bool Toy::init(int lanenum)
{	
	//ファイル名
	std::string filename;
	//画像の種類を引数で変える
	switch (lanenum)
	{
	case 0:	//	赤
		filename = "box1.png";
		this->setTag(1);
		break;
	case 1:	//	青
		filename = "box2.png";
		this->setTag(2);
		break;
	case 2:	//	緑
		filename = "box3.png";
		this->setTag(3);
		break;
	case 3:	//	黄色
		filename = "box4.png";
		this->setTag(4);
		break;
	}
	//	基底クラスの初期化
	if (!Sprite::initWithFile(filename))
	{
		//	スプライトの初期化失敗
		return false;
	}

	//	発射速度の設定
	velocity.x = 0.0f;
	velocity.y = 100.0f;

	//	発射フラグ　true で発射可能
	canShoot = false;
	//	おもちゃになっているかどうかのフラグ
	toyFlag = false;
	//	画像のサイズ　現在は64x64
	this->setScale(2.0f);

	//	Toyの初期化成功
	return true;

}



//	差分計算用
int Toy::difference(int x, int y)
{
	return x > y ? x - y : y - x;
}

//発射
//引数なし
//戻り値なし
void Toy::Shoot()
{
	if (canShoot)
	{
		//MoveBy* shot = MoveBy::create(1.0f, Vec2(0.0f, 640.0f));
		//	現在の場所からvelocityの速度、方向へ移動する処理
		Size bgSize = Director::sharedDirector()->getWinSize();
		MoveBy* move = MoveBy::create(0.1, velocity);

		int countx = (difference(bgSize.width, this->getPosition().x)) / (velocity.x);
		int county = (difference(bgSize.height, this->getPosition().y)) / (velocity.y);

		Repeat *repeat = Repeat::create(move, countx < county ? countx : county);

		this->runAction(repeat);
	}

}

//画像変更
//引数なし
//戻り値なし
void Toy::Change()
{
	//	おもちゃになった
	toyFlag = true;

	//state = 1;
	//ファイル名
	std::string filename;

	//成功していた場合
	if (this->getTag() != 0)
	{
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
	}
	else
	{
		//ランダムのゴミ画像に決定
		switch (rand() % 4)
		{
		case 0:
			filename = "trash1.png";
			break;
		case 1:
			filename = "trash2.png";
			break;
		case 2:
			filename = "trash3.png";
			break;
		case 3:
			filename = "trash4.png";
			break;
		}
	}
	
	//	画像の変更
	Sprite::initWithFile(filename);

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
		this->setColor(Color3B(0x00, 0xff, 0x00));
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

	Size bgSize = Director::sharedDirector()->getWinSize();
	MoveBy* move = MoveBy::create(0.1, velocity / 2);

	int countx = (difference(bgSize.width, this->getPosition().x)) / (velocity.x);
	int county = (difference(bgSize.height, this->getPosition().y)) / (velocity.y / 2);

	Repeat *repeat = Repeat::create(move, countx < county ? countx : county);
	//CallFunc* off = CallFunc::create(CC_CALLBACK_0(Toy::OffConveyor150, this));

	//Spawn* repeat2 = Spawn::create(repeat, off, nullptr);

	this->runAction(repeat);
}

void Toy::OffConveyor(float num)
{
	//	動作停止
	if (this->getPosition().y >= num && canShoot == false)
	{
		this->stopAllActions();
	}
	
}

//失敗したときタグを0にする
//引数なし
//戻り値なし
void Toy::Failed()
{
	this->setTag(0);
}

//場所を確認して発射ができるか確認
void Toy::CheckPosition()
{
	if (this->getPosition().y >= 150.0f)
	{
		canShoot = true;
	}
}

//	おもちゃフラグの確認
bool Toy::getToyFlag()
{
	return toyFlag;
}

//	おもちゃフラグの変更
void Toy::setToyFlag(bool flag)
{
	toyFlag = flag;
}
