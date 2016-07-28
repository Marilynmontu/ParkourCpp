#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "AnimationLayer.h"
#include "StatusLayer.h"

void PlayScene::onEnter()
{
	Node::onEnter();

	addChild(BackgroundLayer::create());
	addChild(AnimationLayer::create());
	addChild(StatusLayer::create());
}
