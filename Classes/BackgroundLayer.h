#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	bool init() override;

	CREATE_FUNC(BackgroundLayer);

	void update(float dt) override;

protected:
	TMXTiledMap *m_map00;
	TMXTiledMap *m_map01;
	float m_mapWidth;
	int m_mapIndex;

	bool checkAndReload(float eyeX);
};

