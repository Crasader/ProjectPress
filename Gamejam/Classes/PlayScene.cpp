#include "PlayScene.h"
#include "ClearScene.h"
#include "LevelSystem.h"
#include "Press.h"
#include "Toy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// 初期化
bool PlayScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//	背景画像
	Sprite* spr = Sprite::create("bbb.png");
	spr->setPosition(640.0f / 2, 960.0f / 2);
	this->addChild(spr);

	//	HUD表示の場所
	Sprite* hud = Sprite::create("hud.png");
	hud->setPosition(640.0f / 2, 960.0f + 200.0f);
	this->addChild(hud,1);

	//	発射レーンの作成
	lane[0] = Sprite::create("lane1.png");
	lane[1] = Sprite::create("lane2.png");
	lane[2] = Sprite::create("lane3.png");
	lane[3] = Sprite::create("lane4.png");

	for (int i = 0; i < 4; i++)
	{
		lane[i]->setPosition(Vec2(110 + (140 * i), 100));
		lane[i]->setColor(Color3B(100, 100, 100));
		this->addChild(lane[i]);
	}

	//	回収レーンの作成
	lastlane = Sprite::create("lane5.png");
	lastlane->setPosition(Vec2(-320.0f, 780.0f));
	this->addChild(lastlane);

	lastlane2 = Sprite::create("lane5.png");
	lastlane2->setPosition(Vec2(320.0f, 780.0f));
	this->addChild(lastlane2);

	//	現在の場所からvelocityの速度、方向へ移動する処理
	Point vel;
	vel.x = 10.0f;
	vel.y = 0.0f;
	MoveBy* move = MoveBy::create(0.1, vel);
	MoveBy* move2 = MoveBy::create(0.1, vel);
	RepeatForever *repeat = RepeatForever::create(move);
	RepeatForever *repeat2 = RepeatForever::create(move2);
	lastlane->runAction(repeat);
	lastlane2->runAction(repeat2);


	//	４つのおもちゃの素の生成　画面外にできる
	for (int i = 0; i < 4; i++)
	{
		m_toy[i] = Toy::create(i);
		m_toy[i]->setPosition(Vec2(110 + (140 * i), -50));
		m_toy[i]->OnConveyor();
		this->addChild(m_toy[i]);
	}



	//	レベルシステムの作成
	level = LevelSystem::create();

	level->set_level(1, 5, 0.8f);
	level->set_level(2, 5, 0.7f);
	level->set_level(3, 7, 0.6f);
	level->set_level(4, 9, 0.5f);
	level->set_level(5, 11, 0.38f);

	//	画像の表示があるのでつなげておく
	this->addChild(level,1);

	//	プレス機の生成
	press = Press::create(level);

	//	プレス機は2秒待ってから開始
	DelayTime* a = DelayTime::create(2.0f);

	CallFunc* act = CallFunc::create(CC_CALLBACK_0(PlayScene::func, this));

	Sequence* b = Sequence::create(a, act, nullptr);

	press->runAction(b);
	//	動かす

	press->setPosition(320.0f, 650.0f);

	this->addChild(press, 1);

	//	タイム表示
	int c = 60;
	String* timer = String::createWithFormat("%i", c);
	timeLabel = Label::createWithSystemFont(timer->getCString(), "arial", 20);
	timeLabel->setPosition(Vec2(320.0f, 900.0f));
	timeLabel->setScale(3.0f);
	timeLabel->setColor(Color3B::BLACK);
	this->addChild(timeLabel,1);


	Sprite* present = Sprite::create("0092.png");
	present->setPosition(Vec2(520.0f, 900.0f));
	present->setScale(0.2f);
	this->addChild(present,1);

	//	成功count表示
	int s = 0;
	String* timer2 = String::createWithFormat("%i", s);
	timeLabel2 = Label::createWithSystemFont(timer2->getCString(), "arial", 20);
	timeLabel2->setPosition(Vec2(590.0f, 900.0f));
	timeLabel2->setScale(2.5f);
	timeLabel2->setColor(Color3B::BLACK);
	this->addChild(timeLabel2, 1);

	// 毎フレーム更新を有効化
	scheduleUpdate();



	// 初期化が正常終了
	return true;
}

// 毎フレーム更新
void PlayScene::update(float delta)
{
	// 3分
	if (m_timecnt < 60 * 60 * 1)//60 * 60 * 3
	{
		m_timecnt++;
		int c = 60 - (m_timecnt / 60);
		timeLabel->setString(StringUtils::toString(c));
	}
	else
	{
		//	終了を表示する

		//	クリックで次のシーンへ移行する

		// 次のシーンを作成する
		Scene* nextScene = ClearScene::create(level->get_Presentcount());
		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

	//	成功countを更新
	timeLabel2->setString(StringUtils::toString(level->get_Presentcount()));

	//	レーンの色の処理
	for (int i = 0; i < 4; i++)
	{
		lane[i]->setColor(Color3B(100, 100, 100));
	}
	//	現在のお題の色を取得
	int Color = press->getPressColor();
	lane[Color - 1]->setColor(Color3B(255, 255, 255));

	
	// 発射ラインにないものを補充する
	for (int i = 0; i < 4; i++)
	{
		//	発射されたおもちゃの素をチェックする
		if (m_toy[i]->getPosition().y >= 200.0f)
		{
			m_toy[i] = Toy::create(i);
			m_toy[i]->setPosition(Vec2(110 + (140 * i), -50));
			m_toy[i]->OnConveyor();
			this->addChild(m_toy[i]);
		}

		//	150のラインに発射不可のおもちゃの素が到達した場合、止める
		m_toy[i]->OffConveyor(150.0f);
		//	150のラインにあれば発射可能フラグを立てる
		m_toy[i]->CheckPosition();
	}

	Vector<Node*> myVector = this->getChildren();
	//Vector<Node*>::iterator myIterator;
	Vector<Node*>::iterator myIterator;

	//	子スプライトの数だけfor	ベクトルの順に
	for (myIterator = myVector.begin(); myIterator != myVector.end(); ++myIterator)
	{
		//	flyをNode*からFly*に
		auto toy = (Toy*)*myIterator;

		//	セットタグしてあればおもちゃ
		if (toy->getTag() >= 1)
		{
			//	回収ラインの真ん中
			if (toy->getPosition().y >= 780.0f && toy->getToyFlag() == true)
			{
				//	780.0fのラインでおもちゃが停止する
				toy->stopAllActions();
				//	ここをもうもう一度読まないようにしてアクションを開始する
				toy->setToyFlag(false);
				Point vel;
				vel.x = 10.0f;
				vel.y = 0.0f;
				MoveBy* move = MoveBy::create(0.1, vel);
				RepeatForever *repeat = RepeatForever::create(move);
				toy->runAction(repeat);
			}
		}
	}
	
	//	現在のレベルを表示
	level->show_level();

	//	回収レーンをループ
	if (lastlane->getPosition().x > 640 + 320)
	{
		lastlane->setPosition(Vec2(-320.0f, 780.0f));
	}
	if (lastlane2->getPosition().x > 640 + 320)
	{
		lastlane2->setPosition(Vec2(-320.0f, 780.0f));
	}


}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//	おもちゃの素とマウスの当たり判定
	for (int i = 0; i < 4; i++)
	{
		//	４つの矩形を保存
		Rect rect_spr[4];
		rect_spr[i] = m_toy[i]->getBoundingBox();

		//	trueになっているとことにあたっている
		m_hit[i] = rect_spr[i].containsPoint(touch_pos);

		//	クリックしたおもちゃの素を
		if (m_hit[i] == true)
		{
			//少しだけ拡大
			m_toy[i]->setScale(2.1f);
		}
	}

	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	double distance = ccpDistance(currentpos, prevpos);
	if (distance > 3)
	{ //スワイプ最新二点間距離３以上
		for (int i = 0; i < 4; i++)
		{
			//	最初にクリックしていたおもちゃの素を
			if (m_hit[i] == true)
			{
				//	発射
				m_toy[i]->Shoot();
				m_hit[i] = false;
			}
		}
	}


	return;
}

// タップが終了したときの処理
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	//	当たり判定を一応すべてfalseにしておく　たぶんいらない
	for (int i = 0; i < 4; i++)
	{
		m_hit[i] = false;
	}
	return;
}

void PlayScene::func()
{
	press->startPress();
}