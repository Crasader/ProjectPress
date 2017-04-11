#pragma once
#include "cocos2d.h"
#include "LevelSystem.h"
#include "Toy.h"

class Press : public cocos2d::Sprite
{
private:

	LevelSystem* Level;	//	現在のレベル
	int Beat;			//	何拍目か管理する
	float fastBeat;		//	1拍目の拍速を保存する
	float BeatSpeed;	//	拍のスピード	
	float Opacity;		//	透明度　割合

	int SuccessiveSuccess; //	現在の連続成功数

	int Color;			//	今回要求している色

	//	色をランダムに決める関数
	int setRand4();
	//	スケジュールによって一定間隔で呼ばれる関数
	void pressBeat(float delta);
	void OpacityFunc1();					//	透明度調整をする
	void OpacityFunc2();					//	透明度調整をする

public:
	static Press* create(LevelSystem* level);				//	プレス機のクリエイト関数
	virtual bool init(LevelSystem* level);				//	プレス機の初期化
	
	int getPressColor();					//	要求している色を取得
	void startPress();					//	プレス機をstartする　スケジュールon
	void setBeatSpeed(float beatspeed);	//	プレス機の速度を変更する
	void SuccessReset();				//	連続成功回数をリセットする
	void levelCheck();					//	拍速の更新処理　アップデートで呼び出す	
	bool toyCheck(Toy* toy);				//	当たり判定
};