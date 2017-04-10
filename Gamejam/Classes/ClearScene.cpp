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

	/*m_clearbg = nullptr;*/
	m_clearbg = Sprite::create("big.png");
	set_pos(640 / 2, 960 / 2);
	this->addChild(m_clearbg);

	// 毎フレーム更新を有効化
	scheduleUpdate();

	//ボタンを作成する
	ui::Button* button = ui::Button::create("Titlebutton.png");
	button->setPosition(Vec2(640/2, 960/2-350));
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

// クリア時の数によって画像が変更される関数
void ClearScene::change_clear(int clear_cnt)
{
	// 削除
	m_clearbg->removeFromParent();
	
	// 判定
	if (clear_cnt < 50)
	{
		m_clearbg = Sprite::create("small.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt >= 50)
	{
		m_clearbg = Sprite::create("normal.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt > 100)
	{
		m_clearbg = Sprite::create("big.png");
		this->addChild(m_clearbg);
	}
	set_pos(640/2,960/2);
}

// 描画位置を設定する関数
void ClearScene::set_pos(float x,float y)
{
	m_clearbg->setPosition(Vec2(x, y));
}