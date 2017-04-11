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
	//	�w�i�摜
	Sprite* spr = Sprite::create("title.png");
	spr->setPosition(640.0f / 2, 960.0f / 2);
	this->addChild(spr);

	// ���t���[���X�V��L����
	scheduleUpdate();

	ui::Button* button = ui::Button::create("CloseNormal.png");
	button->setPosition(Vec2(640.0f / 2, 460.0f / 2));
	button->setScale(4.0f);
	this->addChild(button,1);

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