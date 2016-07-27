#include "MenuScene.h"

Scene * MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();
	// ccp() is deprecated
	auto centerPos = Vec2(winSize.width / 2, winSize.height / 2);
	auto spriteBg = Sprite::create("helloBG.png");
	spriteBg->setPosition(centerPos);
	addChild(spriteBg);

	MenuItemFont::setFontSize(60);
	
	// MenuItemSprite::create(4 parameters) is deprecated
	auto menuItemPlay = MenuItemSprite::create(
		Sprite::create("start_n.png"),
		Sprite::create("start_s.png"),
		CC_CALLBACK_1(MenuScene::onPlay, this));
	auto menu = Menu::createWithItem(menuItemPlay);
	menu->setPosition(centerPos);
	addChild(menu);

	return true;
}

void MenuScene::onPlay(Ref *)
{
	log("==onplay clicked");
}
