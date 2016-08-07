#include "GameOverLayer.h"
#include "PlayScene.h"

bool GameOverLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180)))
		return false;

	auto winSize = Director::getInstance()->getWinSize();
	auto centerPos = Vec2(winSize.width / 2.0f, winSize.height / 2.0f);
	
	MenuItemFont::setFontSize(30);
	auto menuItemRestart = MenuItemSprite::create(
		Sprite::create("restart_n.png"),
		Sprite::create("restart_s.png"),
		CC_CALLBACK_1(GameOverLayer::onRestart, this));
	auto menu = Menu::createWithItem(menuItemRestart);
	menu->setPosition(centerPos);
	this->addChild(menu);

	return true;
}

void GameOverLayer::onRestart(Ref *)
{
	Director::getInstance()->resume();
	Director::getInstance()->runWithScene(PlayScene::create());
}
