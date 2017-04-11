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

	// レベルの情報の初期化
	m_level_info[0] = { 0 };

	// レベルの初期化
	m_level = 0;

	//	成功数の初期化
	m_Presentcount = 0;

	// Lvの画像の初期化
	m_lvnum = Sprite::create("Lv.png");
	m_lvnum->setPosition(Vec2(70.0f, 895.0f));
	m_lvnum->setScale(1.5f);
	this->addChild(m_lvnum,1);

	// 数字の画像の初期化
	m_lv = Sprite::create("one.png");
	m_lv->setScale(2.0f);
	this->addChild(m_lv,1);

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


// レベルを上げる関数
void LevelSystem::up_level()
{
	if (m_level < 5)
	{
		m_level++;
	}
}

// レベルを下げる関数
void LevelSystem::down_level()
{
	if (m_level > 1)
	{
		m_level--;
	}
}


// レベルを上げる関数
void LevelSystem::up_Presentcount()
{
	m_Presentcount++;
}

int LevelSystem::get_Presentcount()
{
	return m_Presentcount;
}

// 現在のレベルのを取得する関数
int LevelSystem::get_level() const
{
	return m_level;
}


// 現在のレベルの情報を取得する関数
LEVEL LevelSystem::get_level_info() const
{
	return m_level_info[m_level - 1];
}


// レベルを表示する関数
void LevelSystem::show_level()
{
	// 判定
	if (m_lv != nullptr)
	{
		// 削除
		m_lv->removeFromParent();
		m_lv = nullptr;

		// レベルによって表示する画像を変更
		switch (m_level)
		{
			case 1:
				m_lv = Sprite::create("one.png");
			
				break;
			case 2:
				m_lv = Sprite::create("two.png");
		
				break;
			case 3:
				m_lv = Sprite::create("three.png");
				
				break;
			case 4:
				m_lv = Sprite::create("four.png");
			
				break;
			case 5:
				m_lv = Sprite::create("five.png");
				
				break;
		}
		m_lv->setScale(2.0f);
		set_pos(110.0f,900.0f);
		this->addChild(m_lv);
	}
}

// 画像の場所をセットする関数
void LevelSystem::set_pos(float x, float y)
{
	m_lv->setPosition(Vec2(x,y));
}

