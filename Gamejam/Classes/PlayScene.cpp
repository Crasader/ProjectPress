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

	//	�w�i�摜
	Sprite* spr = Sprite::create("bbb.png");
	spr->setPosition(640.0f / 2, 960.0f / 2);
	this->addChild(spr);

	//	HUD�\���̏ꏊ
	Sprite* hud = Sprite::create("hud.png");
	hud->setPosition(640.0f / 2, 960.0f + 200.0f);
	this->addChild(hud,1);

	//	���˃��[���̍쐬
	lane[0] = Sprite::create("lane1.png");
	lane[1] = Sprite::create("lane2.png");
	lane[2] = Sprite::create("lane3.png");
	lane[3] = Sprite::create("lane4.png");

	for (int i = 0; i < 4; i++)
	{
		lane[i]->setPosition(Vec2(110 + (140 * i), 100));
		lane[i]->setColor(Color3B(100, 100, 100));
		this->addChild(lane[i]);
	}

	//	������[���̍쐬
	lastlane = Sprite::create("lane5.png");
	lastlane->setPosition(Vec2(-320.0f, 780.0f));
	this->addChild(lastlane);

	lastlane2 = Sprite::create("lane5.png");
	lastlane2->setPosition(Vec2(320.0f, 780.0f));
	this->addChild(lastlane2);

	//	���݂̏ꏊ����velocity�̑��x�A�����ֈړ����鏈��
	Point vel;
	vel.x = 10.0f;
	vel.y = 0.0f;
	MoveBy* move = MoveBy::create(0.1, vel);
	MoveBy* move2 = MoveBy::create(0.1, vel);
	RepeatForever *repeat = RepeatForever::create(move);
	RepeatForever *repeat2 = RepeatForever::create(move2);
	lastlane->runAction(repeat);
	lastlane2->runAction(repeat2);


	//	�S�̂�������̑f�̐����@��ʊO�ɂł���
	for (int i = 0; i < 4; i++)
	{
		m_toy[i] = Toy::create(i);
		m_toy[i]->setPosition(Vec2(110 + (140 * i), -50));
		m_toy[i]->OnConveyor();
		this->addChild(m_toy[i]);
	}



	//	���x���V�X�e���̍쐬
	level = LevelSystem::create();

	level->set_level(1, 5, 0.8f);
	level->set_level(2, 5, 0.7f);
	level->set_level(3, 7, 0.6f);
	level->set_level(4, 9, 0.5f);
	level->set_level(5, 11, 0.38f);

	//	�摜�̕\��������̂łȂ��Ă���
	this->addChild(level,1);

	//	�v���X�@�̐���
	press = Press::create(level);

	//	�v���X�@��2�b�҂��Ă���J�n
	DelayTime* a = DelayTime::create(2.0f);

	CallFunc* act = CallFunc::create(CC_CALLBACK_0(PlayScene::func, this));

	Sequence* b = Sequence::create(a, act, nullptr);

	press->runAction(b);
	//	������

	press->setPosition(320.0f, 650.0f);

	this->addChild(press, 1);

	//	�^�C���\��
	int c = 60;
	String* timer = String::createWithFormat("%i", c);
	timeLabel = Label::createWithSystemFont(timer->getCString(), "arial", 20);
	timeLabel->setPosition(Vec2(320.0f, 900.0f));
	timeLabel->setScale(3.0f);
	timeLabel->setColor(Color3B::BLACK);
	this->addChild(timeLabel,1);


	Sprite* present = Sprite::create("0092.png");
	present->setPosition(Vec2(520.0f, 900.0f));
	present->setScale(0.2f);
	this->addChild(present,1);

	//	����count�\��
	int s = 0;
	String* timer2 = String::createWithFormat("%i", s);
	timeLabel2 = Label::createWithSystemFont(timer2->getCString(), "arial", 20);
	timeLabel2->setPosition(Vec2(590.0f, 900.0f));
	timeLabel2->setScale(2.5f);
	timeLabel2->setColor(Color3B::BLACK);
	this->addChild(timeLabel2, 1);

	// ���t���[���X�V��L����
	scheduleUpdate();



	// ������������I��
	return true;
}

// ���t���[���X�V
void PlayScene::update(float delta)
{
	// 3��
	if (m_timecnt < 60 * 60 * 1)//60 * 60 * 3
	{
		m_timecnt++;
		int c = 60 - (m_timecnt / 60);
		timeLabel->setString(StringUtils::toString(c));
	}
	else
	{
		//	�I����\������

		//	�N���b�N�Ŏ��̃V�[���ֈڍs����

		// ���̃V�[�����쐬����
		Scene* nextScene = ClearScene::create(level->get_Presentcount());
		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}

	//	����count���X�V
	timeLabel2->setString(StringUtils::toString(level->get_Presentcount()));

	//	���[���̐F�̏���
	for (int i = 0; i < 4; i++)
	{
		lane[i]->setColor(Color3B(100, 100, 100));
	}
	//	���݂̂���̐F���擾
	int Color = press->getPressColor();
	lane[Color - 1]->setColor(Color3B(255, 255, 255));

	
	// ���˃��C���ɂȂ����̂��[����
	for (int i = 0; i < 4; i++)
	{
		//	���˂��ꂽ��������̑f���`�F�b�N����
		if (m_toy[i]->getPosition().y >= 200.0f)
		{
			m_toy[i] = Toy::create(i);
			m_toy[i]->setPosition(Vec2(110 + (140 * i), -50));
			m_toy[i]->OnConveyor();
			this->addChild(m_toy[i]);
		}

		//	150�̃��C���ɔ��˕s�̂�������̑f�����B�����ꍇ�A�~�߂�
		m_toy[i]->OffConveyor(150.0f);
		//	150�̃��C���ɂ���Δ��ˉ\�t���O�𗧂Ă�
		m_toy[i]->CheckPosition();
	}

	Vector<Node*> myVector = this->getChildren();
	//Vector<Node*>::iterator myIterator;
	Vector<Node*>::iterator myIterator;

	//	�q�X�v���C�g�̐�����for	�x�N�g���̏���
	for (myIterator = myVector.begin(); myIterator != myVector.end(); ++myIterator)
	{
		//	fly��Node*����Fly*��
		auto toy = (Toy*)*myIterator;

		//	�Z�b�g�^�O���Ă���΂�������
		if (toy->getTag() >= 1)
		{
			//	������C���̐^��
			if (toy->getPosition().y >= 780.0f && toy->getToyFlag() == true)
			{
				//	780.0f�̃��C���ł������Ⴊ��~����
				toy->stopAllActions();
				//	����������������x�ǂ܂Ȃ��悤�ɂ��ăA�N�V�������J�n����
				toy->setToyFlag(false);
				Point vel;
				vel.x = 10.0f;
				vel.y = 0.0f;
				MoveBy* move = MoveBy::create(0.1, vel);
				RepeatForever *repeat = RepeatForever::create(move);
				toy->runAction(repeat);
			}
		}
	}
	
	//	���݂̃��x����\��
	level->show_level();

	//	������[�������[�v
	if (lastlane->getPosition().x > 640 + 320)
	{
		lastlane->setPosition(Vec2(-320.0f, 780.0f));
	}
	if (lastlane2->getPosition().x > 640 + 320)
	{
		lastlane2->setPosition(Vec2(-320.0f, 780.0f));
	}


}

bool PlayScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	//	��������̑f�ƃ}�E�X�̓����蔻��
	for (int i = 0; i < 4; i++)
	{
		//	�S�̋�`��ۑ�
		Rect rect_spr[4];
		rect_spr[i] = m_toy[i]->getBoundingBox();

		//	true�ɂȂ��Ă���Ƃ��Ƃɂ������Ă���
		m_hit[i] = rect_spr[i].containsPoint(touch_pos);

		//	�N���b�N������������̑f��
		if (m_hit[i] == true)
		{
			//���������g��
			m_toy[i]->setScale(2.1f);
		}
	}

	return true;
}

void PlayScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();


	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	double distance = ccpDistance(currentpos, prevpos);
	if (distance > 3)
	{ //�X���C�v�ŐV��_�ԋ����R�ȏ�
		for (int i = 0; i < 4; i++)
		{
			//	�ŏ��ɃN���b�N���Ă�����������̑f��
			if (m_hit[i] == true)
			{
				//	����
				m_toy[i]->Shoot();
				m_hit[i] = false;
			}
		}
	}


	return;
}

// �^�b�v���I�������Ƃ��̏���
void PlayScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	//	�����蔻����ꉞ���ׂ�false�ɂ��Ă����@���Ԃ񂢂�Ȃ�
	for (int i = 0; i < 4; i++)
	{
		m_hit[i] = false;
	}
	return;
}

void PlayScene::func()
{
	press->startPress();
}