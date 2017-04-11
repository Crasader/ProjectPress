//おもちゃの素、おもちゃのクラス宣言
//2017/4/7
//GS2 入山奨

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);			//createで使う初期化
	bool canShoot;					//飛ばせるかどうか
	bool toyFlag;					//おもちゃになっているかどうか
	cocos2d::Point velocity;		//vec
	int difference(int x, int y);	

public:
	static Toy* create(int lanenum);//create
	void Shoot();					//発射
	void Change();					//画像変更
	void OnConveyor();				//自動移動有効化
	void OffConveyor(float num);	//引数のラインで自動移動無効化
	void Failed();					//失敗のフラグ
	void CheckPosition();			//場所チェック(飛ばせるかのフラグを変更)
	bool getToyFlag();				//	おもちゃフラグの確認
	void setToyFlag(bool flag);		//	おもちゃフラグの変更
};

