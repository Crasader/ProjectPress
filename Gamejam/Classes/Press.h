#pragma once
#include "cocos2d.h"

class Press : public cocos2d::Sprite
{
private:

	int Beat;			//	�����ڂ��Ǘ�����
	float fastBeat;		//	1���ڂ̔�����ۑ�����
	float BeatSpeed;	//	���̃X�s�[�h	

	int SuccessiveSuccess; //	���݂̘A��������

	int Collar;			//	����v�����Ă���F

	//	�F�������_���Ɍ��߂�֐�
	int setRand4();
	//	�X�P�W���[���ɂ���Ĉ��Ԋu�ŌĂ΂��֐�
	void pressBeat(float delta);


public:
	static Press* create();				//	�v���X�@�̃N���G�C�g�֐�
	virtual bool init();				//	�v���X�@�̏�����
	
	int getCollar();					//	�v�����Ă���F���擾
	void startPress();					//	�v���X�@��start����@�X�P�W���[��on
	void setBeatSpeed(float beatspeed);	//	�v���X�@�̑��x��ύX����
	void SuccessReset();				//	�A�������񐔂����Z�b�g����
};