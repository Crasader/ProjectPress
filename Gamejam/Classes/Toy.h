//��������̑f�A��������̃N���X�錾
//2017/4/7
//GS2 ���R��

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);			//create�Ŏg��������
	bool initSpawn(int lanenum);	//Spawn�Ŏg��������
	bool canShoot;					//��΂��邩�ǂ���
	cocos2d::Point velocity;		//vec
	int difference(int x, int y);	

public:
	static Toy* create(int lanenum);//create
	static Toy* Spawn(int lanenum);		//������o�Ă���
	void Shoot();					//����
	bool Change();					//�摜�ύX
	void OnConveyor();				//�R���x�A�̏�ɏ�����Ƃ��Ɉړ�����
	void Failed();					//���s�̃t���O
	void CheckPosition();			//�ꏊ�`�F�b�N(��΂��邩�̃t���O��ύX)
};

