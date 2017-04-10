#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void update(float delta) override;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:

	cocos2d::Node* ninjaNode;
	cocos2d::Sprite* ninja;
	cocos2d::Sprite* syuriken;

	cocos2d::Sprite* mato;

	int difference(int, int);
	cocos2d::Point currentpos, prevpos, velocity; //座標保存クラスと速度ベクトル管理クラス
	cocos2d::Sprite* ico; //画像制御

};

#endif // __HELLOWORLD_SCENE_H__
