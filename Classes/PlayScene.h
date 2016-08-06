#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "_chipmunk.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PlayScene : public Scene
{
public:
	CREATE_FUNC(PlayScene);

	void onEnter() override;
	void onExit() override;

	void update(float delta) override;

protected:
	cpSpace *m_space;
	cpShape *m_wallBottom;

	Layer *m_gameLayer;

	void initPhysics();
	void uninitPhysics();

	static cpBool collisionCoinBegin(cpArbiter *arb, cpSpace *space, void *data);
	static cpBool collisionRockBegin(cpArbiter *arb, cpSpace *space, void *data);
	static void removeCoin(cpSpace *space, void *key, void *data);
};
