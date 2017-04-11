#include "ClearScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

//	�N���G�C�g�֐�
ClearScene* ClearScene::create(int level)
{
	ClearScene *press = new (std::nothrow) ClearScene();

	if (press && press->init(level))
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}


// ������
bool ClearScene::init(int level)
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	//	�w�i
	this->change_clear(level);

	// ���t���[���X�V��L����
	scheduleUpdate();

	//�{�^�����쐬����
	ui::Button* button = ui::Button::create("CloseNormal.png");
	button->setPosition(Vec2(640/2, 960/2-350));
	this->addChild(button,2);

	//ui::Button* button = ui::Button::create("Playbutton.png");
	//button->setPosition(Vec2(260, 420));
	//this->addChild(button);

	// �N���b�N���R�[���o�b�N��o�^
	button->addClickEventListener(CC_CALLBACK_1(ClearScene::onButtonClick, this));
	//button->addClickEventListener(CC_CALLBACK_1(ClearScene::onPlayButtonClick, this));

	// ������������I��

	Sprite* present = Sprite::create("0092.png");
	present->setPosition(Vec2(290.0f, 480.0f));
	present->setScale(0.2f);
	this->addChild(present, 1);

	//	����count�\��
	int s = level;
	String* timer2 = String::createWithFormat("%i", s);
	Label* timeLabel2 = Label::createWithSystemFont(timer2->getCString(), "arial", 20);
	timeLabel2->setPosition(Vec2(350.0f, 480.0f));
	timeLabel2->setScale(2.5f);
	timeLabel2->setColor(Color3B::BLACK);
	this->addChild(timeLabel2, 1);
	return true;
}

// ���t���[���X�V
void ClearScene::update(float delta)
{

}

bool ClearScene::onButtonClick(Ref* ref)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = TitleScene::create();
	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return true;
}

//bool ClearScene::onPlayButtonClick(Ref * ref)
//{
//	return false;
//}

bool ClearScene::onPlayButtonClick(Ref* ref)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = PlayScene::create();
	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return true;
}

// �N���A���̐��ɂ���ĉ摜���ύX�����֐�
void ClearScene::change_clear(int clear_cnt)
{
	// �폜
	
	// ����
	if (clear_cnt < 30)
	{
		m_clearbg = Sprite::create("small.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt >= 60)
	{
		m_clearbg = Sprite::create("normal.png");
		this->addChild(m_clearbg);
	}
	else
	{
		m_clearbg = Sprite::create("big.png");
		this->addChild(m_clearbg);
	}
	set_pos(640/2,960/2);
}

// �`��ʒu��ݒ肷��֐�
void ClearScene::set_pos(float x,float y)
{
	m_clearbg->setPosition(Vec2(x, y));
}