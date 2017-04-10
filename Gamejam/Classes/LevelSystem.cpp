#include "LevelSystem.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;

//using namespace cocostudio::timeline;

LevelSystem::LevelSystem()
{

}

LevelSystem::~LevelSystem()
{

}

// レベルの情報をセットする関数
void LevelSystem::set_level(int lv, int count, float beatspd)
{
	m_level = lv;
	m_level_info[m_level].count = count;
	m_level_info[m_level].press_time = beatspd;
}


// レベルを変動する関数
void LevelSystem::fluctuation_level(int lv)
{
	// レベルアップ
	if (/*連続成功数 == 5 &&*/ lv < 5)
	{
		m_level_info[lv] = m_level_info[lv + 1];

		/*連続成功数をリセット*/
	}
	// レベルダウン
	else if (/*成功判定 == false &&*/ lv > 1)
	{
		m_level_info[lv] = m_level_info[lv - 1];
		
		/*連続成功数をリセット*/
	}
}


// 現在のレベルを取得する関数
LEVEL LevelSystem::get_level() const
{
	return m_level_info[m_level];
}

