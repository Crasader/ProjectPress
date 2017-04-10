#pragma once

#include "cocos2d.h"

// ゲームクリアシーン
class ClearScene : public cocos2d::Scene
{
public:
	// create関数の宣言と定義
	CREATE_FUNC(ClearScene);

	bool init();

	void update(float delta) override;

	bool onButtonClick(Ref* ref);
	//bool onPlayButtonClick(Ref* ref);
};