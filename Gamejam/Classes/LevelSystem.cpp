#include "LevelSystem.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;

//using namespace cocostudio::timeline;

// creat関数
LevelSystem* LevelSystem::create()
{
	LevelSystem *pRet = new(std::nothrow) LevelSystem(); 
	if (pRet && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = nullptr; 
		return nullptr; 
	} 
}

// init関数
bool LevelSystem::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_level_info[4] = { 0 };

	m_level = 0;

	return true;
}

// レベルの情報をセットする関数
void LevelSystem::set_level(int lv, int count, float beatspd)
{
	m_level = lv - 1;
	m_level_info[m_level].count = count;
	m_level_info[m_level].press_time = beatspd;
	m_level = 1;
}


// レベルを変動する関数
void LevelSystem::up_level()
{
	m_level++;
}

// レベルを変動する関数
void LevelSystem::down_level()
{
	m_level--;
}



// 現在のレベルのを取得する関数
int LevelSystem::get_level() const
{
	return m_level;
}


// 現在のレベルの情報を取得する関数
LEVEL LevelSystem::get_level_info() const
{
	return m_level_info[m_level];
}

