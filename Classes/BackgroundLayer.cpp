#include "BackgroundLayer.h"
#include <algorithm> // std::remove_if
#include "AnimationLayer.h"
#include "Coin.h"
#include "Rock.h"
#include "Global.h"

using std::unique_ptr;

BackgroundLayer * BackgroundLayer::create(cpSpace * space)
{
	BackgroundLayer *pRet = new(std::nothrow) BackgroundLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool BackgroundLayer::init()
{
	if (!Layer::init())
		return false;

	m_space = nullptr;

	m_map00 = TMXTiledMap::create("map00.tmx");
	this->addChild(m_map00);

	m_mapWidth = m_map00->getContentSize().width;

	m_map01 = TMXTiledMap::create("map01.tmx");
	m_map01->setPosition(m_mapWidth, 0);
	this->addChild(m_map01);

	m_mapIndex = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist");
	m_spriteSheet = SpriteBatchNode::create("background.png");
	this->addChild(m_spriteSheet);

	this->loadObjects(m_map00, 0);
	this->loadObjects(m_map01, 1);

	this->scheduleUpdate();

	return true;
}

void BackgroundLayer::update(float dt)
{
	AnimationLayer *animationLayer =
		this->getParent()->getChildByTag<AnimationLayer *>(LAYER_ANIMATION);
	float eyeX = animationLayer->getEyeX();
	this->checkAndReload(eyeX);
}

bool BackgroundLayer::checkAndReload(float eyeX)
{
	int newMapIndex = (int) (eyeX / m_mapWidth);
	if (newMapIndex == m_mapIndex)
		return false;

	if (newMapIndex % 2 == 0) {
		m_map01->setPositionX(m_mapWidth * (newMapIndex + 1));
		this->loadObjects(m_map01, newMapIndex + 1);
	}
	else {
		m_map00->setPositionX(m_mapWidth * (newMapIndex + 1));
		this->loadObjects(m_map00, newMapIndex + 1);
	}

	removeObjects(newMapIndex - 1);
	m_mapIndex = newMapIndex;
	return true;
}

void BackgroundLayer::loadObjects(TMXTiledMap * map, int mapIndex)
{
	using std::move;

	auto coinGroup = map->getObjectGroup("coin");
	auto coinArray = coinGroup->getObjects();
	for (unsigned i = 0; i < coinArray.size(); i++) {
		Vec2 pos;
		pos.x = coinArray[i].asValueMap()["x"].asFloat() + mapIndex * m_mapWidth;
		pos.y = coinArray[i].asValueMap()["y"].asFloat();
		unique_ptr<Coin> coin(new Coin(m_spriteSheet, m_space, pos));
		coin->setMapIndex(mapIndex);
		m_objects.push_back(move(coin));
	}

	auto rockGroup = map->getObjectGroup("rock");
	auto rockArray = rockGroup->getObjects();
	for (unsigned i = 0; i < rockArray.size(); i++) {
		float x = rockArray[i].asValueMap()["x"].asFloat() + mapIndex * m_mapWidth;
		unique_ptr<Rock> rock(new Rock(m_spriteSheet, m_space, x));
		rock->setMapIndex(mapIndex);
		m_objects.push_back(move(rock));
	}
}

void BackgroundLayer::removeObjects(int mapIndex)
{
	// note: use reference for unique_ptr obj or cpp will perform copy
	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(),
			[=] (auto &obj) { return obj->getMapIndex() == mapIndex; }),
		m_objects.end());
}

#if 0
void BackgroundLayer::removeObjectByShape(cpShape * shape)
{
	auto iter = std::find_if(m_objects.begin(), m_objects.end(),
		[=](auto &obj) { return obj->getShape() == shape; });
	if (iter != m_objects.end())
		m_objects.erase(iter);
}
#endif