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

	for (int i = 0; i < 4; i++)
	{
		m_toy[i] = Toy::create(i);
		this->addChild(m_toy[i]);
	}


	//mato->setPosition(Vec2(880.0f, 320.0f));
	//this->addChild(mato);

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

	// ���̏ꏊ�ɗ����甭�ˉ\
	if (m_toy[0]->getPosition() == Vec2(0.0f, 500.0f))
	{
		m_toy[0] = Toy::create(0);
		this->addChild(m_toy[0]);
		m_hit = true;
	}
	
}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//m_toy[0] = Toy::create(0);
	//this->addChild(m_toy[0]);

	Rect rect_spr = m_toy[0]->getBoundingBox();

	m_hit = rect_spr.containsPoint(touch_pos);


	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	double distance = ccpDistance(currentpos, prevpos);
	if (distance>3)
	{ //�X���C�v�ŐV��_�ԋ����R�ȏ�
		if (m_hit == 1)
		{
			MoveBy* move = MoveBy::create(3.0f, Vec2(0.0f, 700.0f));
			m_toy[0]->runAction(move);
			m_hit = false;
			m_flag = true;
		}

		log("swiped?n"); //check

	}


	return;
}

// �^�b�v���I�������Ƃ��̏���
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{

	return;
}
