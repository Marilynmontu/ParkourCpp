#include "AnimationLayer.h"

bool AnimationLayer::init()
{
	if (!Layer::init())
		return false;

	auto spriteRunner = Sprite::create("runner.png");
	spriteRunner->setPosition(80.0f, 85.0f);

	auto actionTo = MoveTo::create(2.0f, Vec2(300.0f, 85.0f));
	spriteRunner->runAction(actionTo);
	addChild(spriteRunner);

	return true;
}
