#pragma once

#include "cocos2d.h"

// �Q�[���N���A�V�[��
class ClearScene : public cocos2d::Scene
{
public:
	// create�֐��̐錾�ƒ�`
	CREATE_FUNC(ClearScene);

	bool init();

	void update(float delta) override;

	bool onButtonClick(Ref* ref);
	//bool onPlayButtonClick(Ref* ref);

	void change_clear(int clear_cnt);	// �N���A���̐��ɂ���ĉ摜���ύX�����֐�
	void set_pos(float x, float y);		// �`��ʒu��ݒ肷��֐�


	cocos2d::Sprite* m_clearbg;			// �N���A�摜�̃X�v���C�g

};