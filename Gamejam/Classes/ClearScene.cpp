#include "ClearScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

//	クリエイト関数
ClearScene* ClearScene::create(int level)
{
	ClearScene *press = new (std::nothrow) ClearScene();

	if (press && press->init(level))
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}


// 初期化
bool ClearScene::init(int level)
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	//	背景
	this->change_clear(level);

	// 毎フレーム更新を有効化
	scheduleUpdate();

	//ボタンを作成する
	ui::Button* button = ui::Button::create("CloseNormal.png");
	button->setPosition(Vec2(640/2, 960/2-350));
	this->addChild(button,2);

	//ui::Button* button = ui::Button::create("Playbutton.png");
	//button->setPosition(Vec2(260, 420));
	//this->addChild(button);

	// クリック時コールバックを登録
	button->addClickEventListener(CC_CALLBACK_1(ClearScene::onButtonClick, this));
	//button->addClickEventListener(CC_CALLBACK_1(ClearScene::onPlayButtonClick, this));

	// 初期化が正常終了

	Sprite* present = Sprite::create("0092.png");
	present->setPosition(Vec2(290.0f, 480.0f));
	present->setScale(0.2f);
	this->addChild(present, 1);

	//	成功count表示
	int s = level;
	String* timer2 = String::createWithFormat("%i", s);
	Label* timeLabel2 = Label::createWithSystemFont(timer2->getCString(), "arial", 20);
	timeLabel2->setPosition(Vec2(350.0f, 480.0f));
	timeLabel2->setScale(2.5f);
	timeLabel2->setColor(Color3B::BLACK);
	this->addChild(timeLabel2, 1);
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

bool ClearScene::onPlayButtonClick(Ref* ref)
{
	// 次のシーンを作成する
	Scene* nextScene = PlayScene::create();
	// 次のシーンに移行
	_director->replaceScene(nextScene);

	return true;
}

// クリア時の数によって画像が変更される関数
void ClearScene::change_clear(int clear_cnt)
{
	// 削除
	
	// 判定
	if (clear_cnt < 30)
	{
		m_clearbg = Sprite::create("small.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt >= 60)
	{
		m_clearbg = Sprite::create("normal.png");
		this->addChild(m_clearbg);
	}
	else
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