#include "ClearScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// 初期化
bool ClearScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 毎フレーム更新を有効化
	scheduleUpdate();

	//ボタンを作成する
	ui::Button* button = ui::Button::create("Titlebutton.png");
	button->setPosition(Vec2(660, 420));
	this->addChild(button);

	//ui::Button* button = ui::Button::create("Playbutton.png");
	//button->setPosition(Vec2(260, 420));
	//this->addChild(button);

	// クリック時コールバックを登録
	button->addClickEventListener(CC_CALLBACK_1(ClearScene::onButtonClick, this));
	//button->addClickEventListener(CC_CALLBACK_1(ClearScene::onPlayButtonClick, this));

	// 初期化が正常終了
	return true;
}

// 毎フレーム更新
void ClearScene::update(float delta)
{

}

bool ClearScene::onButtonClick(Ref* ref)
{
	// 次のシーンを作成する
	Scene* nextScene = TitleScene::create();
	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return true;
}

//bool ClearScene::onPlayButtonClick(Ref * ref)
//{
//	return false;
//}

//bool ClearScene::onPlayButtonClick(Ref* ref)
//{
//	// 次のシーンを作成する
//	Scene* nextScene = PlayScene::create();
//	// 次のシーンに移行
//	_director->replaceScene(nextScene);
//
//	return true;
//}