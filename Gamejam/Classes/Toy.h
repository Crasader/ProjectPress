//��������̑f�A��������̃N���X�錾
//2017/4/7
//GS2 ���R��

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);			//create�Ŏg��������
	bool canShoot;					//��΂��邩�ǂ���
	bool toyFlag;					//��������ɂȂ��Ă��邩�ǂ���
	cocos2d::Point velocity;		//vec
	int difference(int x, int y);	

public:
	static Toy* create(int lanenum);//create
	void Shoot();					//����
	void Change();					//�摜�ύX
	void OnConveyor();				//�����ړ��L����
	void OffConveyor(float num);	//�����̃��C���Ŏ����ړ�������
	void Failed();					//���s�̃t���O
	void CheckPosition();			//�ꏊ�`�F�b�N(��΂��邩�̃t���O��ύX)
	bool getToyFlag();				//	��������t���O�̊m�F
	void setToyFlag(bool flag);		//	��������t���O�̕ύX
};

