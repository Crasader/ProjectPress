#ifndef __LEVELSYSTEM_SCENE_H__
#define __LEVELSYSTEM_SCENE_H__

#pragma once

#include "cocos2d.h"

// 構造体宣言
struct LEVEL 
{
	int count;			// カウント
	float press_time;		// 時間
};

// レベルシステム
class LevelSystem : public cocos2d::Node
{
	private:
		LEVEL m_level_info[5];		// レベルの情報
		int m_level;				// レベル

	public:
		static LevelSystem * create();		// creat関数
		bool LevelSystem::init();			// init関数
		
		void set_level(int lv, int count, float beatspd);	// レベルの情報をセットする関数
		void up_level();									// レベルを上げる関数
		void down_level();									// レベルを下げる関数

		int get_level() const;									//	現在のレベルを取得

		LEVEL get_level_info() const;							// 現在のレベルの情報を取得する関数
};
#endif
