#ifndef __LEVELSYSTEM_SCENE_H__
#define __LEVELSYSTEM_SCENE_H__

#pragma once

#include "cocos2d.h"

// 構造体宣言
struct LEVEL 
{
	int count;			// カウント
	int press_time;		// 時間
};

// レベルシステム
class LevelSystem : public cocos2d::Node
{
	private:
		LEVEL m_level_info[4];		// レベルの情報
		int m_level;				// レベル

	public:
		LevelSystem();
		~LevelSystem();
		void set_level(int lv, int count, float beatspd);		// レベルの情報をセットする関数
		void fluctuation_level(int lv);							// レベルを変動する関数
		
		LEVEL get_level() const;							// 現在のレベルを取得する関数
};
#endif
