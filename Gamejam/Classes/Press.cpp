#include "Press.h"

USING_NS_CC;
//	�v�������F�������_���Ō��肷��
int Press::setRand4()
{
	//	�P����S�̒l���o��
	return rand() % 4 + 1;
}


//	���̑��x�ɍ��킹�Ĉ��Ԋu�ŌĂ΂��֐�
void Press::pressBeat(float delta)
{
	MoveBy* moveby1 = MoveBy::create(fastBeat, Vec2(0.0f, 50.0f));
	MoveBy* moveby2 = MoveBy::create(fastBeat, Vec2(0.0f, -50.0f));
	//	���݂̔��ɐU�蕪������
	switch (Beat)
	{
	case 0:
		//	�P���ځ@�F�����߂�
		log("Beat:%d", Beat);
		//	�����_���ȂP�|�S���o��
		Collar = setRand4();
		log("Collar:%d", Collar);

		//	�r���Ŕ������ύX���ꂽ���ǂ������ׂ邽�߂�1���ڂ̔�����ۑ�����
		fastBeat = BeatSpeed;

		Beat = 1;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	case 1:
		//	�Q���ڂ͂Ȃɂ����Ȃ�
		log("Beat:%d", Beat);
		Beat = 2;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	case 2:
		//	�R����
		log("Beat:%d", Beat);
		//	�\��������s��

		this->runAction(moveby1);

		Beat = 3;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	case 3:
		//	�S����
		log("Beat:%d", Beat);
		//	�\��������s��

		this->runAction(moveby2);
		//	��������̑f�Ƃ̓����蔻���check����

		//	��������̑f�̕ϊ�

		//	test �A�������񐔂𑝂₷
		SuccessiveSuccess++;
		log("Success:%d", SuccessiveSuccess);

		//	�������O�񂩂�ύX����Ă����ꍇ���̃X�P�W���[�����~�߂ĐV�����X�P�W���[�����n�߂�
		if (fastBeat != BeatSpeed)
		{
			unschedule("beat");
			//	�ŐV�̔��������ƂɃv���X�@�̏����̃X�P�W���[����L��������
			this->schedule(CC_CALLBACK_1(Press::pressBeat, this), BeatSpeed, "beat");
		}

		//	test �A�������񐔂�5�ɂȂ����烊�Z�b�g
		if (SuccessiveSuccess == 5)
		{
			this->SuccessReset();
		}

		Beat = 0;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	}

}

//	�N���G�C�g�֐�
Press* Press::create()
{
	Press *press = new (std::nothrow) Press();

	if (press && press->init())
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}

bool Press::init()
{
	std::string filename = "katoumonster1.png";	//	�v���X�@�̉摜������
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	//	���̏�����
	Beat = 0;
	//	���̑��x�̏����ݒ�
	BeatSpeed = 0.5f;
	//	1��ڂ̔�����ۑ�����ϐ��̏�����
	fastBeat = 0.0f;
	//	�A�������񐔂̏������O
	SuccessiveSuccess = 0;

	//	�v���X�@�̏����ʒu�Ȃ�
	this->setPosition(300.0f, 300.0f);


	return true;
}

int Press::getCollar()
{
	return this->Collar;
}

//	���̊֐����ĂԂƃv���X�@�������n�߂�@�������x��1.0f
void Press::startPress()
{
	//	���������ƂɃv���X�@�̏����̃X�P�W���[����L��������
	this->schedule(CC_CALLBACK_1(Press::pressBeat,this), BeatSpeed,"beat");
}


//	�����𔏑��ɂ���	1.0f = 1�b
void Press::setBeatSpeed(float beatspeed)
{
	BeatSpeed = beatspeed;
}

//	�A�������񐔂̃��Z�b�g
void Press::SuccessReset()
{
	SuccessiveSuccess = 0;
}

