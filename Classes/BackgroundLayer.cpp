#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	if (!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();
	auto centerPos = Vec2(winSize.width / 2, winSize.height / 2);
	auto spriteBG = Sprite::create("PlayBG.png");
	spriteBG->setPosition(centerPos);
	addChild(spriteBG);

	return true;
}
