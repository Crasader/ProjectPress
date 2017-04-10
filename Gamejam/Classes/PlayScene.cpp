#include "PlayScene.h"
#include "ClearScene.h"
#include "LevelSystem.h"
#include "Press.h"
#include "Toy.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// ������
bool PlayScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	

	Toy* mato = Toy::create(0);
	//mato->setPosition(Vec2(880.0f, 320.0f));
	this->addChild(mato);

	// ���t���[���X�V��L����
	scheduleUpdate();

	// ������������I��
	return true;
}

// ���t���[���X�V
void PlayScene::update(float delta)
{
	// 3��
	if (m_timecnt < 10800)
	{
		m_timecnt++;
	}
	else
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = ClearScene::create();
		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}
}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//Rect rect_spr = mato->getBoundingBox();

	//bool hit = rect_spr.containsPoint(touch_pos);

	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	return;
}

// �^�b�v���I�������Ƃ��̏���
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	double distance = ccpDistance(currentpos, prevpos);
	if (distance>3) 
	{ //�X���C�v�ŐV��_�ԋ����R�ȏ�
		log("swiped?n"); //check

	}
	return;
}
