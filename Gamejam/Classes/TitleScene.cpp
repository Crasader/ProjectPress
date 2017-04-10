#include "TitleScene.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// ������
bool TitleScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	// ���t���[���X�V��L����
	scheduleUpdate();

	ui::Button* button = ui::Button::create("Playbutton.png");
	button->setPosition(Vec2(480, 120));
	this->addChild(button);

	// �N���b�N���R�[���o�b�N��o�^
	button->addClickEventListener(CC_CALLBACK_1(TitleScene::onButtonClick, this));

	// ������������I��
	return true;
}

// ���t���[���X�V
void TitleScene::update(float delta)
{

}

bool TitleScene::onButtonClick(Ref* ref)
{
	// ���̃V�[�����쐬����
	Scene* nextScene = PlayScene::create();
	// ���̃V�[���Ɉڍs
	_director->replaceScene(nextScene);

	return true;
}