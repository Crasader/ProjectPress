#ifndef __LEVELSYSTEM_SCENE_H__
#define __LEVELSYSTEM_SCENE_H__

#pragma once

#include "cocos2d.h"

// �\���̐錾
struct LEVEL 
{
	int count;			// �J�E���g
	int press_time;		// ����
};

// ���x���V�X�e��
class LevelSystem : public cocos2d::Node
{
	private:
		LEVEL m_level_info[4];		// ���x���̏��
		int m_level;				// ���x��

	public:
		LevelSystem * create();		// creat�֐�
		bool LevelSystem::init();	// init�֐�
		
		void set_level(int lv, int count, float beatspd);	// ���x���̏����Z�b�g����֐�
		void fluctuation_level(int lv);						// ���x����ϓ�����֐�
		
		LEVEL get_level() const;							// ���݂̃��x�����擾����֐�
};
#endif
