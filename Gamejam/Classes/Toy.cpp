//��������̑f�A��������̃N���X��`
//2017/4/7
//GS2 ���R��

#include "Toy.h"

USING_NS_CC;

//������
//���� ���[��
//�߂�lbool
bool Toy::init(int lanenum)
{
	//�t�@�C����
	std::string filename;

	//�摜�̎�ށA�ꏊ������
	switch (lanenum)
	{
	case 0:
		filename = "box1.png";
		this->setTag(1);
		this->setPosition(Vec2(480 + (64 * lanenum) , 64));
		break;
	case 1:
		filename = "box2.png";
		this->setTag(2);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	case 2:
		filename = "box3.png";
		this->setTag(3);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	case 3:
		filename = "box4.png";
		this->setTag(4);
		this->setPosition(Vec2(480 + (64 * lanenum), 64));
		break;
	}
	
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	
}

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

//����
//�����Ȃ�
//�߂�l�Ȃ�
void Toy::Shoot()
{
	MoveBy* shot = MoveBy::create(1.0f, Vec2(0.0f, 640.0f));
	this->runAction(shot);
}

//�摜�ύX
//�����Ȃ�
//�߂�l�Ȃ�
bool Toy::Change()
{
	//state = 1;
	//�t�@�C����
	std::string filename;

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

	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

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
		this->setColor(Color3B(0xff, 0xff, 0x00));
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
	//�ړ�
	MoveBy* conveyor = MoveBy::create(3.0f, Vec2(0.0f, 1000.0f));
	this->runAction(conveyor);

	//��蒼��
	//this->addChild(create(this->getTag()));
	int tag = this->getTag() - 1;

	//Toy* toy = Toy::create(tag);
	
	//getParent()->addChild(toy);

	//this->removeFromParentAndCleanup(true);

	//return toy;
}

void Toy::Failed()
{
	this->setTag(0);
}