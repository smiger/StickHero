#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player
{
public:
    void SetPosition(Vec2);
    void Walk();
    void Stay();
    void Stop();
    void init();
    void Start(Vec2);
    Sprite* getSprite();
private:
	Sprite* _player;
    Animation* WalkAnimation;
    Animation* StayAnimation;
    Animate* WalkAnimate;
    Animate* StayAnimate;
	Vector<Animate*> animVector;
};
#endif