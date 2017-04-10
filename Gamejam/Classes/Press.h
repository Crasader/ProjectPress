#pragma once
#include "cocos2d.h"

class Press : public cocos2d::Sprite
{
private:

	int Beat;			//	何拍目か管理する
	float fastBeat;		//	1拍目の拍速を保存する
	float BeatSpeed;	//	拍のスピード	

	int SuccessiveSuccess; //	現在の連続成功数

	int Collar;			//	今回要求している色

	//	色をランダムに決める関数
	int setRand4();
	//	スケジュールによって一定間隔で呼ばれる関数
	void pressBeat(float delta);


public:
	static Press* create();				//	プレス機のクリエイト関数
	virtual bool init();				//	プレス機の初期化
	
	int getCollar();					//	要求している色を取得
	void startPress();					//	プレス機をstartする　スケジュールon
	void setBeatSpeed(float beatspeed);	//	プレス機の速度を変更する
	void SuccessReset();				//	連続成功回数をリセットする
};