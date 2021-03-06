#include "BackgroundLayer.h"
#include "GameDefine.h"

bool BackgroundLayer::init()
{
	isStart=false;
	Size MyWinSize = Director::getInstance()->getVisibleSize();
	int RandomNumber = CCRANDOM_0_1()*1000;
	int BGI_Number = RandomNumber%5;
	stage_number = 1;
	NowStage = stage_number  == 0 ? 2:stage_number-1;
	LastStage = NowStage ==0 ? 2:(NowStage-1);
	NextStage = NowStage == 2 ? 0:(NowStage+1);
	// 随机选择游戏欢迎界面时的背景图片
	switch(BGI_Number){
	case 0:
		Image_One = Sprite::create("image/bg/bg1.jpg");
		Image_Two = Sprite::create("image/bg/bg1.jpg");
		break;
	case 1:
		Image_One = Sprite::create("image/bg/bg2.jpg");
		Image_Two = Sprite::create("image/bg/bg2.jpg");
		break;
	case 2:
		Image_One = Sprite::create("image/bg/bg3.jpg");
		Image_Two = Sprite::create("image/bg/bg3.jpg");
		break;
	case 3:
		Image_One = Sprite::create("image/bg/bg4.jpg");
		Image_Two = Sprite::create("image/bg/bg4.jpg");
		break;
	case 4:
		Image_One = Sprite::create("image/bg/bg5.jpg");
		Image_Two = Sprite::create("image/bg/bg5.jpg");
		break;
	default:
		break;
	}
	Image_One->setPosition(MyWinSize.width/2,MyWinSize.height/2);
	Image_Two->setPosition(MyWinSize.width/2 + Image_Two->getContentSize().width,MyWinSize.height/2);
	this->addChild(Image_One,1);
	this->addChild(Image_Two,1);
	// 游戏欢迎界面的标题图片
	GameName = Sprite::create("image/uires_1.png");
	GameName->setPosition(MyWinSize.width/2,MyWinSize.height/5*4);
	this->addChild(GameName,2);
	//开始菜单
	StartBtn = MenuItemSprite::create(
		Sprite::create("image/uires_2.png"),
		Sprite::create("image/uires_2.png"),
		NULL,this ,menu_selector(BackgroundLayer::Start));
	StartBtn->setPosition(MyWinSize.width/2,MyWinSize.height/2+8);
	MoveTo* StartBtnMoveDown = MoveTo::create(2,Vec2(MyWinSize.width/2,MyWinSize.height/2-8));
	MoveTo* StartBtnMoveUp = MoveTo::create(2,Vec2(MyWinSize.width/2,MyWinSize.height/2+5));
	auto StartMoveSeq = Sequence::create(StartBtnMoveDown,StartBtnMoveUp,NULL);
	auto StartMoveRepeat = RepeatForever::create(StartMoveSeq);
	StartBtn->runAction(StartMoveRepeat);
	menu = Menu::create(StartBtn,NULL);
	menu->setPosition(0,0);
	this->addChild(menu,2);
	//平台
	// 对所有平台初始化
	for (int i = 0; i < 3; i++)
	{
		stage_sprite[i] = Sprite::create("image/stage1.png");
	}
	stage_sprite[0]->setScaleX(30);
	stage_sprite[0]->setPosition(Vec2(MyWinSize.width / 2, stage_sprite[0]->getContentSize().height / 4));
	// 另两个平台的位置
	for (int i = 1; i < 3; i++)
	{
		stage_sprite[i]->setPosition(Vec2(MyWinSize.width + stage_sprite[i]->getScaleX()*stage_sprite[i]->getContentSize().width, stage_sprite[i]->getContentSize().height / 2));
	}

	for (int i = 0; i < 3; i++)
	{
		this->addChild(stage_sprite[i], 3);
	}
	// 单点触摸事件
	touch_listener = EventListenerTouchOneByOne::create();
	touch_listener->setSwallowTouches(true);
	touch_listener->onTouchBegan = CC_CALLBACK_2(BackgroundLayer::onTouchBegan,this);
	touch_listener->onTouchMoved = CC_CALLBACK_2(BackgroundLayer::onTouchMoved,this);
	touch_listener->onTouchEnded = CC_CALLBACK_2(BackgroundLayer::onTouchEnded,this);
	touch_listener->onTouchCancelled = CC_CALLBACK_2(BackgroundLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
	//添加英雄
	My_Player.init();
	My_Player.SetPosition(Vec2(MyWinSize.width/2,stage_sprite[0]->getContentSize().height/4*3));
	this->addChild(My_Player.getSprite(),5);
	My_Player.Stay();

	//添加棍子
	stick = Sprite::create("image/stick1.png");
	stick->setAnchorPoint(Vec2(0.5,0));
	stick->setPosition(-stick->getContentSize().width,-stick->getContentSize().height);
	this->addChild(stick,5);

	return true;
}
void BackgroundLayer::Start(Ref* pSender)
{
	log("1\start");
	//移除按钮、标题
	this->removeChild(menu);
	this->removeChild(GameName);
	MoveTo* stageMove1 = MoveTo::create(0.2,Vec2(STAGE_SCALE,stage_sprite[0]->getContentSize().height/2));
	MoveTo* playerMove = MoveTo::create(0.2,Vec2(STAGE_SCALE+stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX()/2 - My_Player.getSprite()->getContentSize().width/2 - 5,stage_sprite[0]->getContentSize().height));
	stage_sprite[0]->runAction(stageMove1);
	My_Player.getSprite()->runAction(playerMove);
	isStart=true;
	initStick();
	addStage();


}
void BackgroundLayer::addStage()
{
	log("2\addStage");
	Size MyWinSize = Director::getInstance()->getVisibleSize();
	stage_sprite[stage_number]->setScaleX(10+CCRANDOM_0_1()*40);
	stage_sprite[stage_number]->setPosition(Vec2(MyWinSize.width + stage_sprite[stage_number]->getScaleX()*stage_sprite[stage_number]->getContentSize().width, stage_sprite[stage_number]->getContentSize().height/2));
	MoveTo* stageMove = MoveTo::create(0.2, Vec2(MyWinSize.width/2 + CCRANDOM_0_1()*MyWinSize.width/3, stage_sprite[stage_number]->getContentSize().height/2));
	stage_sprite[stage_number]->runAction(stageMove);
	log("stage_number=%d",stage_number);
	if(stage_number+1<=2)
	{
		stage_number+=1;
	}
	else
	{
		stage_number = 0;
	}
	//NowStage的编号是[0,2]对应stage_number的编号是[1,3]
	NowStage = stage_number  == 0 ? 2:stage_number-1;
	LastStage = NowStage ==0 ? 2:(NowStage-1);
	NextStage = NowStage == 2 ? 0:(NowStage+1);
}
void BackgroundLayer::stageMove()
{
	log("3\stageMove");
	initStick();
	MoveTo* NowstageMove = MoveTo::create(0.2, Vec2(STAGE_SCALE,stage_sprite[0]->getContentSize().height/2));
	stage_sprite[NowStage]->runAction(NowstageMove);
	MoveTo* playerMove = MoveTo::create(0.2,Vec2(STAGE_SCALE+stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX()/2 - My_Player.getSprite()->getContentSize().width/2 - 5,stage_sprite[0]->getContentSize().height));
	My_Player.getSprite()->runAction(playerMove);
	MoveTo* LaststageMove = MoveTo::create(0.2, Vec2(-stage_sprite[LastStage]->getContentSize().width * stage_sprite[LastStage]->getScaleX(),stage_sprite[0]->getContentSize().height/2));
	stage_sprite[LastStage]->runAction(LaststageMove);
	addStage();
	ResetStick();
}
bool BackgroundLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	log("4\onTouchBegan");
	if(isStart){
		addStick();
	}else{
		return false;
	}
	isStart = false;
	return true;
}
void BackgroundLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

void BackgroundLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	log("5\onTouchEnded");
	StopStick();
	RotateStickAndGo();

}
void BackgroundLayer::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
}

void BackgroundLayer::addStick()
{
	log("6\addStick");
	// 棍子设置在平台的右上角那个点上
	stick->setPosition(StickPoint);
	this->schedule(schedule_selector(BackgroundLayer::StickLength));
}

void BackgroundLayer::StickLength(float)
{
	stick->setScaleY(stick->getScaleY()+5);
}
void BackgroundLayer::StopStick()
{
	// 存储棍子的长度
	TouchLength = stick->getContentSize().height*stick->getScaleY();
	this->unschedule(schedule_selector(BackgroundLayer::StickLength));
}
void BackgroundLayer::RotateStickAndGo()
{
	log("7\RotateStickAndGo");
	// 算出棍子到下个平台的最小距离、最大距离
	DestLengthMin = abs(stage_sprite[LastStage]->getPositionX() - stage_sprite[NowStage]->getPositionX()) - stage_sprite[LastStage]->getContentSize().width*stage_sprite[LastStage]->getScaleX()/2 - stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX()/2;
	DestLengthMax = DestLengthMin + stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX();

	CallFunc* MoveToNext = CallFunc::create(CC_CALLBACK_0(BackgroundLayer::PlayerMoveToNextStage, this));
	RotateTo* Ro_Stick = RotateTo::create(0.5, 90); //旋转90度
	Sequence* GOGO = Sequence::create(Ro_Stick,MoveToNext, NULL);

	CallFunc* GoCallBack = CallFunc::create(CC_CALLBACK_0(BackgroundLayer::PlayerMove, this));
	Sequence* StickDown = Sequence::create(Ro_Stick,GoCallBack,NULL);
	log("TouchLength=%d,DestLengthMin=%d,DestLengthMax=%d", TouchLength,DestLengthMin,DestLengthMax);
	log("LastStage=%d,NowStage=%d", LastStage,NowStage);
	// 判断计算出的棍子长度是不是在我们最大距离和最小距离之间
	if(TouchLength<DestLengthMin || TouchLength > DestLengthMax)
	{
		stick->runAction(StickDown);
	}
	else if(TouchLength >= DestLengthMin && TouchLength <=DestLengthMax)
	{
		stick->runAction(GOGO);
	}

}

void BackgroundLayer::ResetStick()
{
	log("9\ResetStick");
	stick->setRotation(0);
	stick->setPosition(-stick->getContentSize().width,-stick->getContentSize().height);
	stick->setScaleY(1);

}
void BackgroundLayer::initStick()
{
	log("10\initStick");
	StickPoint.x = STAGE_SCALE + stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX()/2;
	StickPoint.y = stage_sprite[NowStage]->getContentSize().height;
}
void BackgroundLayer::PlayerDown()
{
	log("11\PlayerDown");

	MoveBy* Down = MoveBy::create(0.1,Vec2(0,-800));
	My_Player.getSprite()->runAction(Down);
	RotateTo* Ro_Stick = RotateTo::create(0.5, 180); //旋转180度
	Sequence* StickDown = Sequence::create(Ro_Stick, NULL);
	stick->runAction(StickDown);
	over = GameOverLayer::create();
	this->addChild(over,8);

}
void BackgroundLayer::PlayerMove()
{
	log("12\PlayerMove");
	MoveBy* GO = MoveBy::create((float)TouchLength/MOVE_SPEED,Vec2(TouchLength,0));
	CallFunc* DownCallBack = CallFunc::create(CC_CALLBACK_0(BackgroundLayer::PlayerDown, this));
	Sequence* Goon = Sequence::create(GO,DownCallBack,NULL);
	My_Player.getSprite()->runAction(Goon);
}
void BackgroundLayer::PlayerMoveToNextStage()
{
	log("13\PlayerMoveToNextStage");
	StageAndPlayerMove();
}
void BackgroundLayer::StageAndPlayerMove()
{
	log("8\StageAndPlayerMove");
	Vec2 dest;
	dest.x = stage_sprite[NowStage]->getPosition().x + stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX()/2 - My_Player.getSprite()->getContentSize().width/2 - 5;
	dest.y = stage_sprite[NowStage]->getContentSize().height;
	float dist = dest.x - My_Player.getSprite()->getPosition().x;
	log("dist=%f", dist);
	MoveTo* playermove = MoveTo::create(dist / MOVE_SPEED, dest);
	My_Player.Stop();
	My_Player.Walk();
	CallFunc* moveCallBack = CallFunc::create(CC_CALLBACK_0(BackgroundLayer::stageMove, this));
	CallFunc* moveCallBack1 = CallFunc::create([&]{isStart = true;});
	CallFunc* moveCallBack2 = CallFunc::create([&]{
		My_Player.Stay();
	});
	Sequence* Move = Sequence::create(playermove,moveCallBack,moveCallBack1,moveCallBack2,NULL);
	My_Player.getSprite()->runAction(Move);

}