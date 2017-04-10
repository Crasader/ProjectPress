#include "ClearScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// ������
bool ClearScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	/*m_clearbg = nullptr;*/
	m_clearbg = Sprite::create("big.png");
	set_pos(640 / 2, 960 / 2);
	this->addChild(m_clearbg);

	// ���t���[���X�V��L����
	scheduleUpdate();

	//�{�^�����쐬����
	ui::Button* button = ui::Button::create("Titlebutton.png");
	button->setPosition(Vec2(640/2, 960/2-350));
	this->addChild(button);

	//ui::Button* button = ui::Button::create("Playbutton.png");
	//button->setPosition(Vec2(260, 420));
	//this->addChild(button);

	// �N���b�N���R�[���o�b�N��o�^
	button->addClickEventListener(CC_CALLBACK_1(ClearScene::onButtonClick, this));
	//button->addClickEventListener(CC_CALLBACK_1(ClearScene::onPlayButtonClick, this));

	// ������������I��
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

//bool ClearScene::onPlayButtonClick(Ref* ref)
//{
//	// ���̃V�[�����쐬����
//	Scene* nextScene = PlayScene::create();
//	// ���̃V�[���Ɉڍs
//	_director->replaceScene(nextScene);
//
//	return true;
//}

// �N���A���̐��ɂ���ĉ摜���ύX�����֐�
void ClearScene::change_clear(int clear_cnt)
{
	// �폜
	m_clearbg->removeFromParent();
	
	// ����
	if (clear_cnt < 50)
	{
		m_clearbg = Sprite::create("small.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt >= 50)
	{
		m_clearbg = Sprite::create("normal.png");
		this->addChild(m_clearbg);
	}
	else if (clear_cnt > 100)
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