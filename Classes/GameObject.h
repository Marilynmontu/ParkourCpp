#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameObject
{
public:
	GameObject(cpSpace *space);
	virtual ~GameObject();

	int getMapIndex() const { return m_mapIndex; }
	void setMapIndex(int value) { m_mapIndex = value; }
	
	cpShape *getShape() const { return m_shape; }

protected:
	int m_mapIndex;
	cpSpace *m_space;
	cpShape *m_shape;
	cpBody *m_body;
	PhysicsSprite *m_sprite;
};
