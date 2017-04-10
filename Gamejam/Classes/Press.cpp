#include "audio\include\AudioEngine.h"
#include "Press.h"

USING_NS_CC;
using namespace cocos2d::experimental;

//	�v�������F�������_���Ō��肷��
int Press::setRand4()
{
	//	�P����S�̒l���o��
	return rand() % 4 + 1;
}


//	���̑��x�ɍ��킹�Ĉ��Ԋu�ŌĂ΂��֐�
void Press::pressBeat(float delta)
{
	//MoveBy* moveby1 = MoveBy::create(fastBeat, Vec2(0.0f, 50.0f));
	//MoveBy* moveby2 = MoveBy::create(fastBeat, Vec2(0.0f, -50.0f));
	ScaleTo* PreliminaryOperation = ScaleTo::create(BeatSpeed / 3,1.2f);	//	�\������

	//	�v���X�@�𗎂Ƃ�
	ScaleTo* PressActionPress = ScaleTo::create(BeatSpeed / 3, 0.8f);	//	�v���X����
	//	�v���X�@�̓����x��1�ɂ���
	CallFunc* PressActionOpacty1 = CallFunc::create(CC_CALLBACK_0(Press::OpacityFunc1, this));
	//	�v���X�@�������ʒu�ɖ߂�
	ScaleTo* PressActionReturn = ScaleTo::create(BeatSpeed / 3, 1.1f);
	//	�v���X�@�̓����x��0.8�ɂ���
	CallFunc* PressActionOpacty2 = CallFunc::create(CC_CALLBACK_0(Press::OpacityFunc2, this));

	Sequence* PressAction = Sequence::create(PressActionOpacty1,PressActionPress, PressActionOpacty2, PressActionReturn, nullptr);


	//	���݂̔��ɐU�蕪������
	switch (Beat)
	{
	case 0:
		//	������
		AudioEngine::play2d("button01a.ogg");

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
		//	������
		AudioEngine::play2d("button01a.ogg");

		//	�Q���ڂ͂Ȃɂ����Ȃ�
		log("Beat:%d", Beat);
		Beat = 2;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	case 2:
		//	������
		AudioEngine::play2d("button01a.ogg");

		//	�R����
		log("Beat:%d", Beat);

		//	�\��������s��
		//this->runAction(moveby1);
		this->runAction(PreliminaryOperation);

		Beat = 3;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	case 3:
		//	������
		AudioEngine::play2d("select01.ogg");
		
		//	�S����
		log("Beat:%d", Beat);

		//	�v���X�@������
		//this->runAction(moveby2);
		this->runAction(PressAction);

		//	��������̑f�Ƃ̓����蔻�肪true�Ȃ�

		Node* parent = this->getParent();

		Vector<Node*> myVector = parent->getChildren();

		//Vector<Node*>::iterator myIterator;
		Vector<Node*>::iterator myIterator;

		//	�q�X�v���C�g�̐�����for	�x�N�g���̏���
		for (myIterator = myVector.begin(); myIterator != myVector.end(); ++myIterator)
		{
			
			//	fly��Node*����Fly*��
			auto toy = (Toy*)*myIterator;

			//	�Z�b�g�^�O���Ă���΂�������̑f
			if(toy->getTag() >= 1)
			{
				//	��������̑f�Ɠ���������true
				if (toyCheck(toy))
				{
					//	�F�������Ă�����true
					if (this->Collar == toy->getTag())
					{
						//	�������̉���炷
						
						int id = AudioEngine::play2d("se_atari.ogg");
						AudioEngine::setVolume(id,3.0f);

						//	��������ɂȂ�
						toy->Change();
					}
					else
					{
						//	���s�̉���炷
						int id = AudioEngine::play2d("se_hazure.ogg");
						AudioEngine::setVolume(id, 3.0f);
						//	���s�i�ɕς���
						toy->Failed();
						toy->Change();
					}
				}
			}
		}

		

		//	��������̑f�̕ϊ�����


		//	test �A�������񐔂𑝂₷
		SuccessiveSuccess++;
		log("Success:%d", SuccessiveSuccess);
		//	���x�����}�b�N�X�Ȃ�X�V���Ȃ�

		//	test �A�������񐔂��K�v���ɂȂ����烌�x���A�b�v���ă��Z�b�g
		if (SuccessiveSuccess == Level->get_level_info().count)
		{
			//	���x���A�b�v
			Level->up_level();
			//	�A�������񐔃J�E���g���Z�b�g
			this->SuccessReset();
			//	test�������O�񂩂�ύX����Ă����ꍇ���̃X�P�W���[�����~�߂ĐV�����X�P�W���[�����n�߂�
			unschedule("beat");
			//	���݂̃��x���̑��x���X�V����
			this->levelCheck();
			//	�ŐV�̔��������ƂɃv���X�@�̏����̃X�P�W���[����L��������
			this->schedule(CC_CALLBACK_1(Press::pressBeat, this), BeatSpeed, "beat");
		}
	



		Beat = 0;	//	���ɂ��̊֐����Ă΂ꂽ�Ƃ��Ɏ��̔��ɐi��
		break;
	}

}

//	�N���G�C�g�֐�
Press* Press::create(LevelSystem* level)
{
	Press *press = new (std::nothrow) Press();

	if (press && press->init(level))
	{
		press->autorelease();
		return press;
	}
	CC_SAFE_DELETE(press);
	return nullptr;
}

bool Press::init(LevelSystem* level)
{
	std::string filename = "press.png";	//	�v���X�@�̉摜������
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	//	���O�ǂݍ���
	AudioEngine::preload("button01a.ogg");
	AudioEngine::preload("select01.ogg");
	AudioEngine::preload("se_atari.ogg");
	AudioEngine::preload("se_hazure.ogg");

	//	���x���̏�����
	Level = level;

	//	���̏�����
	Beat = 0;
	//	���̑��x�̏����ݒ�
	BeatSpeed = Level->get_level_info().press_time;

	//	1��ڂ̔�����ۑ�����ϐ��̏�����
	fastBeat = 0;

	//	�A�������񐔂̏�����0
	SuccessiveSuccess = 0;

	//	���������x
	Opacity = 0.8f;

	//	�v���X�@�̏����ʒu�Ȃ�
	this->setOpacity(255 * Opacity);

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

//	�����x�������ݒ�ŕs�����ɖ߂�
void Press::OpacityFunc1()
{
	float op;
	op = this->getOpacity();
	this->setOpacity(op / Opacity);
}


//	�����x�������ݒ�œ����ɖ߂�
void Press::OpacityFunc2()
{
	this->setOpacity(255 * Opacity);
}

//	���݂̃��x���𒲂ׂă��x���ɍ��킹�Ĕ�����ύX���邽�߂Ɏg��
void Press::levelCheck()
{
	BeatSpeed = Level->get_level_info().press_time;
}

//	�v���X�@����������̑f�Ƃ̓����蔻��@�������Ă�����true
bool Press::toyCheck(Toy* toy)
{

	if (toy->getPosition().y < this->getPosition().y + 20 && toy->getPosition().y > this->getPosition().y - 70)	//��������̑f����������
	{

		return true;
	}
	return false;
}