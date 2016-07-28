#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AnimationLayer : public Layer
{
public:
	static AnimationLayer *create(cpSpace *space);
	bool init() override;

	virtual ~AnimationLayer();

protected:
	SpriteBatchNode *m_spriteSheet;
	Action *m_runningAction;
	PhysicsSprite *m_sprite;
	cpSpace *m_space;
	cpBody *m_body;
	cpShape *m_shape;
};
