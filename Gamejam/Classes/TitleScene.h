#pragma once

#include "cocos2d.h"

// �^�C�g���V�[��
class TitleScene : public cocos2d::Scene
{
public:
	// create�֐��̐錾�ƒ�`
	CREATE_FUNC(TitleScene);

	bool init();

	void update(float delta) override;

	bool onButtonClick(Ref* ref);
};