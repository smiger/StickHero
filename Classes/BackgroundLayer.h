#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__


#include "cocos2d.h"
#include "Player.h"
#include "GameOverLayer.h"

USING_NS_CC;

class BackgroundLayer : public Scene
{
public:
	virtual bool init();
	void BGIMove(float);
	void Start(Ref*);
	void addStage();
	void stageMove();
	CREATE_FUNC(BackgroundLayer);
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
	virtual void onTouchCancelled(Touch* pTouch, Event* pEvent);
	void addStick();
	void StickLength(float);
	void StopStick();
	void RotateStickAndGo();
	void StageAndPlayerMove();
	void ResetStick();
	void initStick();
	void PlayerDown();
	void PlayerMove();
	void PlayerMoveToNextStage();
private:
	Sprite* Image_One;
	Sprite* Image_Two;
	Sprite* GameName;
	MenuItemSprite* StartBtn;
	Menu* menu;
	Sprite* stage_sprite[3];
	int stage_number;
	EventListenerTouchOneByOne* touch_listener;
	bool isStart;
	Player My_Player;
	Sprite* stick;
	Vec2 StickPoint;
	int TouchLength;
	int NowStage;
	int LastStage;
	int NextStage;
	int DestLengthMin;
	int DestLengthMax;
	GameOverLayer* over;
};
#endif