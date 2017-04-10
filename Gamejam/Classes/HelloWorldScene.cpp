#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

	ninjaNode = Node::create();
	this->addChild(ninjaNode);

	ninja = Sprite::create("ninja.png");
	ninja->setPosition(Vec2(480.0f, 320.0f));
	ninja->setFlipX(true);
	ninja->setScale(0.4);
	ninjaNode->addChild(ninja);

	mato = Sprite::create("mato.png");
	mato->setPosition(Vec2(880.0f, 320.0f));
	this->addChild(mato);



	//syuriken = Sprite::create("syuriken.png");
	//syuriken->setPosition(Vec2(480.0f, 320.0f));
	//syuriken->setScale(0.1f);

	//ninjaNode->addChild(syuriken);

	scheduleUpdate();


    return true;
}



bool HelloWorld::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{

	Vec2 touch_pos = touch->getLocation();

	ninja->setPosition(touch_pos);


	syuriken = Sprite::create("syuriken.png");
	syuriken->setPosition(touch_pos);
	syuriken->setScale(0.1f);
	syuriken->setTag(10);
	ninjaNode->addChild(syuriken);


	MoveBy* action1 = MoveBy::create(0.5f,Vec2(1000.0f,0.0f));
	RotateBy* action2 = RotateBy::create(3.0f, 360.0f * 100);
	
	Spawn* action3 = Spawn::create(action1, action2, nullptr);


	syuriken->runAction(action3);
	

	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	Vec2 touch_pos = touch->getLocation();

	ninja->setPosition(touch_pos);


	syuriken = Sprite::create("syuriken.png");
	syuriken->setPosition(Vec2(touch_pos.x + 50.0f,touch_pos.y -10.0f));
	syuriken->setScale(0.1f);

	syuriken->setTag(10);

	ninjaNode->addChild(syuriken);

	MoveBy* action1 = MoveBy::create(0.5f, Vec2(1000.0f, 0.0f));
	RotateBy* action2 = RotateBy::create(3.0f, 360.0f * 20);

	Spawn* action3 = Spawn::create(action1, action2, nullptr);


	syuriken->runAction(action3);


	syuriken->runAction(action1);

	prevpos = touch->getPreviousLocation();
	currentpos = touch->getLocation(); //get previous positon

	return;
}

// タップが終了したときの処理
void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event)
{
	double distance = ccpDistance(currentpos, prevpos);
	if (distance>1) { //スワイプ最新二点間距離３以上
		log("swiped?n"); //check
		velocity = ccpSub(currentpos, prevpos); //currentpos-prevpos
		Size bgSize = Director::sharedDirector()->getWinSize(); //画面サイズ
		MoveBy* throwanimation = MoveBy::create(0.1, velocity); //0.1秒にvelocityだけ進む
		ico = Sprite::create("ninja.png"); //画像読み込み
		ico->setPosition(currentpos); //画像位置設定
		this->addChild(ico); //画面張り付け thisは自分自身のポインタ
		int countx = (difference(bgSize.width, currentpos.x)) / (velocity.x);
		int county = (difference(bgSize.height, currentpos.y)) / (velocity.y);
		Repeat *repeat = Repeat::create(throwanimation, countx<county ? countx : county); //適切な回数でリピート
		ico->runAction(repeat); //アニメーションスタート
		repeat->setTag(0); //animetionタグセット
	}
	return;
}

int HelloWorld::difference(int x, int y) { //差分計算
	return x>y ? x - y : y - x;
}

void HelloWorld::update(float delta)
{
	if (syuriken != nullptr)
	{
		//if (syuriken->getPosition().x  >= 950.0f)
		//{
		//	syuriken->stopActionByTag(1);
		//	syuriken->setPosition(Vec2(950.0f,syuriken->getPosition().y));
		//}



		Sprite* spr;


		for (auto child:ninjaNode->getChildren())
		{
			spr = (Sprite*)child;
			if (spr->getTag() == 10)
			{
				
				Rect rect_syuriken = spr->getBoundingBox();
				Rect rect_mato = mato->boundingBox();
				Node* parent;
				parent = spr->getParent();
				rect_syuriken = RectApplyAffineTransform(rect_syuriken, parent->getNodeToWorldAffineTransform());
				parent = mato->getParent();
				rect_mato = RectApplyAffineTransform(rect_mato, parent->getNodeToWorldAffineTransform());

				bool hit = rect_mato.intersectsRect(rect_syuriken);

				if (hit)
				{
					spr->stopAllActions();
				}


				if (spr->getPosition().x >= 950.0f)
				{
					spr->stopAllActions();
					spr->setPosition(Vec2(950.0f, spr->getPosition().y));
				}

			}

		}
	}
}
