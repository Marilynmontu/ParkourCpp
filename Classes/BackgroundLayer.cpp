#include "BackgroundLayer.h"
#include "AnimationLayer.h"
#include "Global.h"

bool BackgroundLayer::init()
{
	if (!Layer::init())
		return false;

	m_map00 = TMXTiledMap::create("map00.tmx");
	this->addChild(m_map00);

	m_mapWidth = m_map00->getContentSize().width;

	m_map01 = TMXTiledMap::create("map01.tmx");
	m_map01->setPosition(m_mapWidth, 0);
	this->addChild(m_map01);

	m_mapIndex = 0;

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
	}
	else {
		m_map00->setPositionX(m_mapWidth * (newMapIndex + 1));
	}

	m_mapIndex = newMapIndex;
	return true;
}
