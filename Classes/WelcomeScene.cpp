#include "WelcomeScene.h"
#include "BackgroundLayer.h"

Scene* WelcomeScene::createScene()
{
	// 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool WelcomeScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/anim1/anim1.plist");
	BackgroundLayer* BGI_Layer = BackgroundLayer::create();
	this->addChild(BGI_Layer,1,1);
	
	return true;
}