#pragma once

#include <memory>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameObject;

class BackgroundLayer : public Layer
{
public:
	static BackgroundLayer *create(cpSpace *space);
	bool init() override;

	void update(float dt) override;

	void removeObjectByShape(cpShape *shape);

protected:
	TMXTiledMap *m_map00;
	TMXTiledMap *m_map01;
	float m_mapWidth;
	int m_mapIndex;

	SpriteBatchNode *m_spriteSheet;
	cpSpace *m_space;

	std::vector<std::unique_ptr<GameObject>> m_objects;

	bool checkAndReload(float eyeX);
	void loadObjects(TMXTiledMap *map, int mapIndex);
	void removeObjects(int mapIndex);
};

