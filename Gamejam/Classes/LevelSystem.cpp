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
	m_level_info[4] = { 0 };

	// ���x���̏�����
	m_level = 0;

	// Lv�̉摜�̏�����
	m_lvnum = Sprite::create("Lv.png");
	m_lvnum->setPosition(Vec2(115.0f, 150.0f));
	this->addChild(m_lvnum);

	// �����̉摜�̏�����
	m_lv = Sprite::create("one.png");
	this->addChild(m_lv);

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
	m_level++;
}

// ���x����������֐�
void LevelSystem::down_level()
{
	m_level--;
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
				this->addChild(m_lv);
				break;
			case 2:
				m_lv = Sprite::create("two.png");
				this->addChild(m_lv);
				break;
			case 3:
				m_lv = Sprite::create("three.png");
				this->addChild(m_lv);
				break;
			case 4:
				m_lv = Sprite::create("four.png");
				this->addChild(m_lv);
				break;
			case 5:
				m_lv = Sprite::create("five.png");
				this->addChild(m_lv);
				break;
		}
		set_pos(150.0f,150.0f);
	}
}

// �摜�̏ꏊ���Z�b�g����֐�
void LevelSystem::set_pos(float x, float y)
{
	m_lv->setPosition(Vec2(x,y));
}

