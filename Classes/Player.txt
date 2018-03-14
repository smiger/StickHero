#include "Player.h"

void Player::init()
{
	_player = Sprite::createWithSpriteFrameName("stay1.png");
	_player->setAnchorPoint(Vec2(0.5,0));

	//1
	Vector<SpriteFrame*> frameVector;
	for(int i = 1;i<=5;i++)
	{
		char pngName[260] = {0};
		sprintf(pngName, "stay%d.png",i);
		frameVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName));

	}
	StayAnimation = Animation::createWithSpriteFrames(frameVector, 0.1f);
	StayAnimation->setRestoreOriginalFrame(false);
	StayAnimation->setLoops(-1);//无限循环
	StayAnimate = Animate::create(StayAnimation);
	animVector.pushBack(StayAnimate);//将动画装进容器
	//2
	frameVector.clear();
	for(int i = 1;i<=5;i++)
	{
		char pngName[260] = {0};
		sprintf(pngName, "walk%d.png",i);
		frameVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(pngName));
	}
	WalkAnimation = Animation::createWithSpriteFrames(frameVector, 1.0f);
	WalkAnimation->setRestoreOriginalFrame(false);
	WalkAnimation->setLoops(-1);//无限循环
	WalkAnimate = Animate::create(WalkAnimation);
	animVector.pushBack(WalkAnimate);//将动画装进容器

}
Sprite* Player::getSprite()
{
	return _player;
}
void Player::SetPosition(Vec2 _pos)
{
	_player->setPosition(_pos);
}

//4
void Player::Stay()
{
	auto animate = animVector.at(0);
	_player->runAction(animate);
}
//5
void Player::Stop()
{
	_player->stopAllActions();
}
//6
void Player::Walk()
{
	auto animate = animVector.at(1);
	_player->runAction(animate);
}
//7
void Player::Start(Vec2 _dec)
{
	MoveTo* move = MoveTo::create(0.2f, _dec);
	_player->runAction(move);
}