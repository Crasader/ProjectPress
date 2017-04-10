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

	

	Toy* mato = Toy::create(0);
	//mato->setPosition(Vec2(880.0f, 320.0f));
	this->addChild(mato);

	// 毎フレーム更新を有効化
	scheduleUpdate();

	// 初期化が正常終了
	return true;
}

// 毎フレーム更新
void PlayScene::update(float delta)
{
	// 3分
	if (m_timecnt < 10800)
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
}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//Rect rect_spr = mato->getBoundingBox();

	//bool hit = rect_spr.containsPoint(touch_pos);

	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	return;
}

// タップが終了したときの処理
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	double distance = ccpDistance(currentpos, prevpos);
	if (distance>3) 
	{ //スワイプ最新二点間距離３以上
		log("swiped?n"); //check

	}
	return;
}
