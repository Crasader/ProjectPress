#pragma once

#include "cocos2d.h"

// ゲームクリアシーン
class ClearScene : public cocos2d::Scene
{
public:

	static ClearScene * create(int level);

	bool init(int level);

	void update(float delta) override;

	bool onButtonClick(Ref* ref);
	//bool onPlayButtonClick(Ref* ref);

	bool onPlayButtonClick(Ref * ref);

	void change_clear(int clear_cnt);	// クリア時の数によって画像が変更される関数
	void set_pos(float x, float y);		// 描画位置を設定する関数


	cocos2d::Sprite* m_clearbg;			// クリア画像のスプライト

	int num;

};