#pragma once

#include "cocos2d.h"

// �v���C�V�[��
class PlayScene: public cocos2d::Scene
{
public:
	// create�֐��̐錾�ƒ�`
	CREATE_FUNC(PlayScene);

	bool init();

	
	cocos2d::Point currentpos, prevpos, velocity; //���W�ۑ��N���X�Ƒ��x�x�N�g���Ǘ��N���X
	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	

	int m_timecnt;
};