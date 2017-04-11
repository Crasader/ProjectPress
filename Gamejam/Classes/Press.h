#pragma once
#include "cocos2d.h"
#include "LevelSystem.h"
#include "Toy.h"

class Press : public cocos2d::Sprite
{
private:

	LevelSystem* Level;	//	���݂̃��x��
	int Beat;			//	�����ڂ��Ǘ�����
	float fastBeat;		//	1���ڂ̔�����ۑ�����
	float BeatSpeed;	//	���̃X�s�[�h	
	float Opacity;		//	�����x�@����

	int SuccessiveSuccess; //	���݂̘A��������

	int Color;			//	����v�����Ă���F

	//	�F�������_���Ɍ��߂�֐�
	int setRand4();
	//	�X�P�W���[���ɂ���Ĉ��Ԋu�ŌĂ΂��֐�
	void pressBeat(float delta);
	void OpacityFunc1();					//	�����x����������
	void OpacityFunc2();					//	�����x����������

public:
	static Press* create(LevelSystem* level);				//	�v���X�@�̃N���G�C�g�֐�
	virtual bool init(LevelSystem* level);				//	�v���X�@�̏�����
	
	int getPressColor();					//	�v�����Ă���F���擾
	void startPress();					//	�v���X�@��start����@�X�P�W���[��on
	void setBeatSpeed(float beatspeed);	//	�v���X�@�̑��x��ύX����
	void SuccessReset();				//	�A�������񐔂����Z�b�g����
	void levelCheck();					//	�����̍X�V�����@�A�b�v�f�[�g�ŌĂяo��	
	bool toyCheck(Toy* toy);				//	�����蔻��
};