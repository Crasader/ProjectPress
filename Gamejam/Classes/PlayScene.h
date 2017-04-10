#pragma once

#include "cocos2d.h"

// プレイシーン
class PlayScene: public cocos2d::Scene
{
public:
	// create関数の宣言と定義
	CREATE_FUNC(PlayScene);

	bool init();

	
	cocos2d::Point currentpos, prevpos, velocity; //座標保存クラスと速度ベクトル管理クラス
	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	

	int m_timecnt;
};