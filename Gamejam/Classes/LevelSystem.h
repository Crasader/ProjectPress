#ifndef __LEVELSYSTEM_SCENE_H__
#define __LEVELSYSTEM_SCENE_H__

#pragma once

#include "cocos2d.h"

// �\���̐錾
struct LEVEL 
{
	int count;				// �J�E���g
	float press_time;		// ����
};

// ���x���V�X�e��
class LevelSystem : public cocos2d::Node
{
	private:
		LEVEL m_level_info[5];		// ���x���̏��
		int m_level;				// ���x��
		cocos2d::Sprite* m_lv;		// Lv�̃X�v���C�g
		cocos2d::Sprite* m_lvnum;	// �����̃X�v���C�g

	public:
		static LevelSystem* create();		// creat�֐�
		bool init();						// init�֐�
		
		void set_level(int lv, int count, float beatspd);	// ���x���̏����Z�b�g����֐�
		void up_level();									// ���x�����グ��֐�
		void down_level();									// ���x����������֐�

		int get_level() const;								// ���݂̃��x�����擾

		LEVEL get_level_info() const;						// ���݂̃��x���̏����擾����֐�

		void show_level();									// ���x����\������֐�

		void set_pos(float x,float y);						// �摜�̏ꏊ���Z�b�g����֐�

};
#endif
