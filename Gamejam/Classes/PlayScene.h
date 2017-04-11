#pragma once

#include "cocos2d.h"
#include "Press.h"
#include "Toy.h"
#include "LevelSystem.h"

// プレイシーン
class PlayScene: public cocos2d::Scene
{
public:
	// create関数の宣言と定義
	CREATE_FUNC(PlayScene);

	bool init();

	
	cocos2d::Point currentpos, prevpos, velocity; //座標保存クラスと速度ベクトル管理クラス
	//cocos2d::Toy* mato;

	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void func();

	cocos2d::Label* timeLabel;
	cocos2d::Label* timeLabel2;
	LevelSystem* level;
	cocos2d::Sprite* lane[4];
	cocos2d::Sprite* lastlane;
	cocos2d::Sprite* lastlane2;
	Press* press;
	Toy* m_toy[4];
	int m_timecnt;
	int m_hit[4];
	int m_flag;
};