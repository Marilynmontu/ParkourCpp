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
	
	void update(float dt) override;
	void onExit() override;

	virtual ~AnimationLayer();

	float getEyeX();

protected:
	SpriteBatchNode *m_spriteSheet;
	Action *m_runningAction;
	Action *m_jumpUpAction;
	Action *m_jumpDownAction;
	PhysicsSprite *m_sprite;
	cpSpace *m_space;
	cpBody *m_body;
	cpShape *m_shape;

	PhysicsDebugNode *m_debugNode;

	int m_stat;

	void initAction();
	void jump();
};
