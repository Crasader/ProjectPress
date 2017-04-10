//おもちゃの素、おもちゃのクラス宣言
//2017/4/7
//GS2 入山奨

#pragma once

#include "cocos2d.h"

class Toy : public cocos2d::Sprite
{
private:
	bool init(int lanenum);			//createで使う初期化
	bool initSpawn(int lanenum);	//Spawnで使う初期化
	bool canShoot;					//飛ばせるかどうか
	cocos2d::Point velocity;		//vec
	int difference(int x, int y);	

public:
	static Toy* create(int lanenum);//create
	static Toy* Spawn(int lanenum);		//下から出てくる
	void Shoot();					//発射
	bool Change();					//画像変更
	void OnConveyor();				//コンベアの上に乗ったときに移動する
	void Failed();					//失敗のフラグ
	void CheckPosition();			//場所チェック(飛ばせるかのフラグを変更)
};

