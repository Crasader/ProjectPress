#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// 初期化
bool TitleScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 毎フレーム更新を有効化
	scheduleUpdate();

	ui::Button* button = ui::Button::create("Playbutton.png");
	button->setPosition(Vec2(480, 120));
	this->addChild(button);

	// クリック時コールバックを登録
	button->addClickEventListener(CC_CALLBACK_1(TitleScene::onButtonClick, this));

	// 初期化が正常終了
	return true;
}

// 毎フレーム更新
void TitleScene::update(float delta)
{

}

bool TitleScene::onButtonClick(Ref* ref)
{
	// 次のシーンを作成する
	Scene* nextScene = PlayScene::create();
	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return true;
}