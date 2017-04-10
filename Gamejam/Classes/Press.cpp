#include "audio\include\AudioEngine.h"
#include "Press.h"

USING_NS_CC;
using namespace cocos2d::experimental;

//	要求される色をランダムで決定する
int Press::setRand4()
{
	//	１から４の値が出る
	return rand() % 4 + 1;
}


//	拍の速度に合わせて一定間隔で呼ばれる関数
void Press::pressBeat(float delta)
{
	//MoveBy* moveby1 = MoveBy::create(fastBeat, Vec2(0.0f, 50.0f));
	//MoveBy* moveby2 = MoveBy::create(fastBeat, Vec2(0.0f, -50.0f));
	ScaleTo* PreliminaryOperation = ScaleTo::create(BeatSpeed / 3,1.2f);	//	予備動作

	//	プレス機を落とす
	ScaleTo* PressActionPress = ScaleTo::create(BeatSpeed / 3, 0.8f);	//	プレス動作
	//	プレス機の透明度を1にする
	CallFunc* PressActionOpacty1 = CallFunc::create(CC_CALLBACK_0(Press::OpacityFunc1, this));
	//	プレス機を初期位置に戻す
	ScaleTo* PressActionReturn = ScaleTo::create(BeatSpeed / 3, 1.1f);
	//	プレス機の透明度を0.8にする
	CallFunc* PressActionOpacty2 = CallFunc::create(CC_CALLBACK_0(Press::OpacityFunc2, this));

	Sequence* PressAction = Sequence::create(PressActionOpacty1,PressActionPress, PressActionOpacty2, PressActionReturn, nullptr);


	//	現在の拍に振り分けられる
	switch (Beat)
	{
	case 0:
		//	音が鳴る
		AudioEngine::play2d("button01a.ogg");

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
		//	音が鳴る
		AudioEngine::play2d("button01a.ogg");

		//	２拍目はなにもしない
		log("Beat:%d", Beat);
		Beat = 2;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	case 2:
		//	音が鳴る
		AudioEngine::play2d("button01a.ogg");

		//	３拍目
		log("Beat:%d", Beat);

		//	予備動作を行う
		//this->runAction(moveby1);
		this->runAction(PreliminaryOperation);

		Beat = 3;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	case 3:
		//	音が鳴る
		AudioEngine::play2d("select01.ogg");
		
		//	４拍目
		log("Beat:%d", Beat);

		//	プレス機が動く
		//this->runAction(moveby2);
		this->runAction(PressAction);

		//	おもちゃの素との当たり判定をcheckする

		//	おもちゃの素の変換する

		if (Level->get_level() == 2)
		{
			int a = 1999;
		}

		//	test 連続成功回数を増やす
		SuccessiveSuccess++;
		log("Success:%d", SuccessiveSuccess);

		//	test 連続成功回数が必要数になったらレベルアップしてリセット
		if (SuccessiveSuccess == Level->get_level_info().count)
		{

			//	レベルアップ
			Level->up_level();
			//	連続成功回数カウントリセット
			this->SuccessReset();
			//	test拍速が前回から変更されていた場合今のスケジュールを止めて新しいスケジュールを始める
			unschedule("beat");
			//	現在のレベルの速度を更新する
			this->levelCheck();
			//	最新の拍速をもとにプレス機の処理のスケジュールを有効化する
			this->schedule(CC_CALLBACK_1(Press::pressBeat, this), BeatSpeed, "beat");
		}



		Beat = 0;	//	次にこの関数が呼ばれたときに次の拍に進む
		break;
	}

}

//	クリエイト関数
Press* Press::create(LevelSystem* level)
{
	Press *press = new (std::nothrow) Press();

	if (press && press->init(level))
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}

bool Press::init(LevelSystem* level)
{
	std::string filename = "press.png";	//	プレス機の画像を入れる
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	//	事前読み込み
	AudioEngine::preload("button01a.ogg");
	AudioEngine::preload("select01.ogg");

	//	レベルの初期化
	Level = level;

	//	拍の初期化
	Beat = 0;
	//	拍の速度の初期設定
	BeatSpeed = Level->get_level_info().press_time;

	//	1回目の拍速を保存する変数の初期化
	fastBeat = 0;

	//	連続成功回数の初期化0
	SuccessiveSuccess = 0;

	//	初期透明度
	Opacity = 0.8f;

	//	プレス機の初期位置など
	this->setOpacity(255 * Opacity);


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

//	透明度を初期設定で不透明に戻す
void Press::OpacityFunc1()
{
	float op;
	op = this->getOpacity();
	this->setOpacity(op / Opacity);
}


//	透明度を初期設定で透明に戻す
void Press::OpacityFunc2()
{
	this->setOpacity(255 * Opacity);
}

//	現在のレベルを調べてレベルに合わせて拍速を変更するために使う
void Press::levelCheck()
{
	BeatSpeed = Level->get_level_info().press_time;
}

//	プレス機をおもちゃの素との当たり判定　当たっていたらtrue
//bool Press::toyCheck()
//{
//
//}