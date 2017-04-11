#include "LevelSystem.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;

//using namespace cocostudio::timeline;

// creat�֐�
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

// init�֐�
bool LevelSystem::init()
{
	if (!Node::init())
	{
		return false;
	}

	// ���x���̏��̏�����
	m_level_info[0] = { 0 };

	// ���x���̏�����
	m_level = 0;

	//	�������̏�����
	m_Presentcount = 0;

	// Lv�̉摜�̏�����
	m_lvnum = Sprite::create("Lv.png");
	m_lvnum->setPosition(Vec2(70.0f, 895.0f));
	m_lvnum->setScale(1.5f);
	this->addChild(m_lvnum,1);

	// �����̉摜�̏�����
	m_lv = Sprite::create("one.png");
	m_lv->setScale(2.0f);
	this->addChild(m_lv,1);

	return true;
}

// ���x���̏����Z�b�g����֐�
void LevelSystem::set_level(int lv, int count, float beatspd)
{
	m_level = lv - 1;
	m_level_info[m_level].count = count;
	m_level_info[m_level].press_time = beatspd;
	m_level = 1;
}


// ���x�����グ��֐�
void LevelSystem::up_level()
{
	if (m_level < 5)
	{
		m_level++;
	}
}

// ���x����������֐�
void LevelSystem::down_level()
{
	if (m_level > 1)
	{
		m_level--;
	}
}


// ���x�����グ��֐�
void LevelSystem::up_Presentcount()
{
	m_Presentcount++;
}

int LevelSystem::get_Presentcount()
{
	return m_Presentcount;
}

// ���݂̃��x���̂��擾����֐�
int LevelSystem::get_level() const
{
	return m_level;
}


// ���݂̃��x���̏����擾����֐�
LEVEL LevelSystem::get_level_info() const
{
	return m_level_info[m_level - 1];
}


// ���x����\������֐�
void LevelSystem::show_level()
{
	// ����
	if (m_lv != nullptr)
	{
		// �폜
		m_lv->removeFromParent();
		m_lv = nullptr;

		// ���x���ɂ���ĕ\������摜��ύX
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

// �摜�̏ꏊ���Z�b�g����֐�
void LevelSystem::set_pos(float x, float y)
{
	m_lv->setPosition(Vec2(x,y));
}

