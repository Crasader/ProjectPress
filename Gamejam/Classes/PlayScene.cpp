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


	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	for (int i = 0; i < 4; i++)
	{
		m_toy[i] = Toy::create(i);
		this->addChild(m_toy[i]);
	}


	//mato->setPosition(Vec2(880.0f, 320.0f));
	//this->addChild(mato);

	// 毎フレーム更新を有効化
	scheduleUpdate();

	// 初期化が正常終了
	return true;
}

// 毎フレーム更新
void PlayScene::update(float delta)
{
	// 3分
	if (m_timecnt < 180)
	{
		m_timecnt++;
	}
	else
	{
		// 次のシーンを作成する
		Scene* nextScene = ClearScene::create();
		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

	// 一定の場所に来たら発射可能
	if (m_toy[0]->getPosition() == Vec2(0.0f, 500.0f))
	{
		m_toy[0] = Toy::create(0);
		this->addChild(m_toy[0]);
		m_hit = true;
	}
	
}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//m_toy[0] = Toy::create(0);
	//this->addChild(m_toy[0]);

	Rect rect_spr = m_toy[0]->getBoundingBox();

	m_hit = rect_spr.containsPoint(touch_pos);


	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	double distance = ccpDistance(currentpos, prevpos);
	if (distance>3)
	{ //スワイプ最新二点間距離３以上
		if (m_hit == 1)
		{
			MoveBy* move = MoveBy::create(3.0f, Vec2(0.0f, 700.0f));
			m_toy[0]->runAction(move);
			m_hit = false;
			m_flag = true;
		}

		log("swiped?n"); //check

	}


	return;
}

// タップが終了したときの処理
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{

	return;
}
