#include "Press.h"

USING_NS_CC;
//	要求される色をランダムで決定する
int Press::setRand4()
{
	//	１から４の値が出る
	return rand() % 4 + 1;
}


//	拍の速度に合わせて一定間隔で呼ばれる関数
void Press::pressBeat(float delta)
{
	MoveBy* moveby1 = MoveBy::create(fastBeat, Vec2(0.0f, 50.0f));
	MoveBy* moveby2 = MoveBy::create(fastBeat, Vec2(0.0f, -50.0f));
	//	現在の拍に振り分けられる
	switch (Beat)
	{
	case 0:
		//	１拍目　色を決める
		log("Beat:%d", Beat);
		//	ランダムな１－４が出る
		Collar = setRand4();
		log("Collar:%d", Collar);

		//	途中で拍速が変更されたかどうか調べるために1拍目の拍速を保存する
		fastBeat = BeatSpeed;

		Beat = 1;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	case 1:
		//	２拍目はなにもしない
		log("Beat:%d", Beat);
		Beat = 2;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	case 2:
		//	３拍目
		log("Beat:%d", Beat);
		//	予備動作を行う

		this->runAction(moveby1);

		Beat = 3;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	case 3:
		//	４拍目
		log("Beat:%d", Beat);
		//	予備動作を行う

		this->runAction(moveby2);
		//	おもちゃの素との当たり判定をcheckする

		//	おもちゃの素の変換

		//	test 連続成功回数を増やす
		SuccessiveSuccess++;
		log("Success:%d", SuccessiveSuccess);

		//	拍速が前回から変更されていた場合今のスケジュールを止めて新しいスケジュールを始める
		if (fastBeat != BeatSpeed)
		{
			unschedule("beat");
			//	最新の拍速をもとにプレス機の処理のスケジュールを有効化する
			this->schedule(CC_CALLBACK_1(Press::pressBeat, this), BeatSpeed, "beat");
		}

		//	test 連続成功回数が5になったらリセット
		if (SuccessiveSuccess == 5)
		{
			this->SuccessReset();
		}

		Beat = 0;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	}

}

//	クリエイト関数
Press* Press::create()
{
	Press *press = new (std::nothrow) Press();

	if (press && press->init())
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}

bool Press::init()
{
	std::string filename = "katoumonster1.png";	//	プレス機の画像を入れる
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	//	拍の初期化
	Beat = 0;
	//	拍の速度の初期設定
	BeatSpeed = 0.5f;
	//	1回目の拍速を保存する変数の初期化
	fastBeat = 0.0f;
	//	連続成功回数の初期化０
	SuccessiveSuccess = 0;

	//	プレス機の初期位置など
	this->setPosition(300.0f, 300.0f);


	return true;
}

int Press::getCollar()
{
	return this->Collar;
}

//	この関数を呼ぶとプレス機が動き始める　初期速度は1.0f
void Press::startPress()
{
	//	拍速をもとにプレス機の処理のスケジュールを有効化する
	this->schedule(CC_CALLBACK_1(Press::pressBeat,this), BeatSpeed,"beat");
}


//	引数を拍速にする	1.0f = 1秒
void Press::setBeatSpeed(float beatspeed)
{
	BeatSpeed = beatspeed;
}

//	連続成功回数のリセット
void Press::SuccessReset()
{
	SuccessiveSuccess = 0;
}

