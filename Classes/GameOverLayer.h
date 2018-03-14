#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
 
class GameOverLayer
:public Layer
{
public:
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    void ReStart(Ref*);
};
#endif