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
};