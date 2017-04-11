//��������̑f�A��������̃N���X��`
//2017/4/7
//GS2 ���R��

#include "Toy.h"

USING_NS_CC;



//����
//���� ���[��
//�߂�lbool
Toy* Toy::create(int lanenum)
{
	Toy *toy = new (std::nothrow) Toy();
	if (toy && toy->init(lanenum))
	{
		toy->autorelease();
		return toy;
	}
	CC_SAFE_DELETE(toy);
	return nullptr;
}

//������
//���� ���[��
//�߂�lbool
bool Toy::init(int lanenum)
{	
	//�t�@�C����
	std::string filename;
	//�摜�̎�ނ������ŕς���
	switch (lanenum)
	{
	case 0:	//	��
		filename = "box1.png";
		this->setTag(1);
		break;
	case 1:	//	��
		filename = "box2.png";
		this->setTag(2);
		break;
	case 2:	//	��
		filename = "box3.png";
		this->setTag(3);
		break;
	case 3:	//	���F
		filename = "box4.png";
		this->setTag(4);
		break;
	}
	//	���N���X�̏�����
	if (!Sprite::initWithFile(filename))
	{
		//	�X�v���C�g�̏��������s
		return false;
	}

	//	���ˑ��x�̐ݒ�
	velocity.x = 0.0f;
	velocity.y = 100.0f;

	//	���˃t���O�@true �Ŕ��ˉ\
	canShoot = false;
	//	��������ɂȂ��Ă��邩�ǂ����̃t���O
	toyFlag = false;
	//	�摜�̃T�C�Y�@���݂�64x64
	this->setScale(2.0f);

	//	Toy�̏���������
	return true;

}



//	�����v�Z�p
int Toy::difference(int x, int y)
{
	return x > y ? x - y : y - x;
}

//����
//�����Ȃ�
//�߂�l�Ȃ�
void Toy::Shoot()
{
	if (canShoot)
	{
		//MoveBy* shot = MoveBy::create(1.0f, Vec2(0.0f, 640.0f));
		//	���݂̏ꏊ����velocity�̑��x�A�����ֈړ����鏈��
		Size bgSize = Director::sharedDirector()->getWinSize();
		MoveBy* move = MoveBy::create(0.1, velocity);

		int countx = (difference(bgSize.width, this->getPosition().x)) / (velocity.x);
		int county = (difference(bgSize.height, this->getPosition().y)) / (velocity.y);

		Repeat *repeat = Repeat::create(move, countx < county ? countx : county);

		this->runAction(repeat);
	}

}

//�摜�ύX
//�����Ȃ�
//�߂�l�Ȃ�
void Toy::Change()
{
	//	��������ɂȂ���
	toyFlag = true;

	//state = 1;
	//�t�@�C����
	std::string filename;

	//�������Ă����ꍇ
	if (this->getTag() != 0)
	{
		//�����_���̂�������Ɍ���
		switch (rand() % 4)
		{
		case 0:
			filename = "toy1.png";
			break;
		case 1:
			filename = "toy2.png";
			break;
		case 2:
			filename = "toy3.png";
			break;
		case 3:
			filename = "toy4.png";
			break;
		}
	}
	else
	{
		//�����_���̃S�~�摜�Ɍ���
		switch (rand() % 4)
		{
		case 0:
			filename = "trash1.png";
			break;
		case 1:
			filename = "trash2.png";
			break;
		case 2:
			filename = "trash3.png";
			break;
		case 3:
			filename = "trash4.png";
			break;
		}
	}
	
	//	�摜�̕ύX
	Sprite::initWithFile(filename);

	//�^�O��񂩂�F������
	switch (this->getTag())
	{
	case 1:
		this->setColor(Color3B(0xff, 0x00, 0x00));
		break;
	case 2:
		this->setColor(Color3B(0x00, 0x00, 0xff));
		break;
	case 3:
		this->setColor(Color3B(0x00, 0xff, 0x00));
		break;
	case 4:
		this->setColor(Color3B(0xff, 0xff, 0x00));
		break;
	}



}

//�R���x�A�̏�ɏ�����Ƃ��̏���
//�����Ȃ�
//�߂�l�Ȃ�
void Toy::OnConveyor()
{

	Size bgSize = Director::sharedDirector()->getWinSize();
	MoveBy* move = MoveBy::create(0.1, velocity / 2);

	int countx = (difference(bgSize.width, this->getPosition().x)) / (velocity.x);
	int county = (difference(bgSize.height, this->getPosition().y)) / (velocity.y / 2);

	Repeat *repeat = Repeat::create(move, countx < county ? countx : county);
	//CallFunc* off = CallFunc::create(CC_CALLBACK_0(Toy::OffConveyor150, this));

	//Spawn* repeat2 = Spawn::create(repeat, off, nullptr);

	this->runAction(repeat);
}

void Toy::OffConveyor(float num)
{
	//	�����~
	if (this->getPosition().y >= num && canShoot == false)
	{
		this->stopAllActions();
	}
	
}

//���s�����Ƃ��^�O��0�ɂ���
//�����Ȃ�
//�߂�l�Ȃ�
void Toy::Failed()
{
	this->setTag(0);
}

//�ꏊ���m�F���Ĕ��˂��ł��邩�m�F
void Toy::CheckPosition()
{
	if (this->getPosition().y >= 150.0f)
	{
		canShoot = true;
	}
}

//	��������t���O�̊m�F
bool Toy::getToyFlag()
{
	return toyFlag;
}

//	��������t���O�̕ύX
void Toy::setToyFlag(bool flag)
{
	toyFlag = flag;
}
