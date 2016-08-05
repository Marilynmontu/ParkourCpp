#pragma once

#include "cocos2d.h"

USING_NS_CC;

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
};
