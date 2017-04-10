#pragma once

#include "cocos2d.h"
#include "Toy.h"

// �v���C�V�[��
class PlayScene: public cocos2d::Scene
{
public:
	// create�֐��̐錾�ƒ�`
	CREATE_FUNC(PlayScene);

	bool init();

	
	cocos2d::Point currentpos, prevpos, velocity; //���W�ۑ��N���X�Ƒ��x�x�N�g���Ǘ��N���X
	//cocos2d::Toy* mato;

	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	
	Toy* m_toy[4];
	int m_timecnt;
	int m_hit;
	int m_flag;
};