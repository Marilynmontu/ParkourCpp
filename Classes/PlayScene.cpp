#include "PlayScene.h"
#include <chipmunk.h>
#include "BackgroundLayer.h"
#include "AnimationLayer.h"
#include "StatusLayer.h"
#include "Global.h"

#include <string>
#include <sstream>

void PlayScene::onEnter()
{
	Node::onEnter();
	initPhysics();

	addChild(BackgroundLayer::create());
	addChild(AnimationLayer::create(m_space));
	addChild(StatusLayer::create());

	scheduleUpdate();
}

void PlayScene::onExit()
{
	uninitPhysics();
}

void PlayScene::update(float delta)
{
	std::stringstream ss;
	ss << "delta:" << delta << std::endl;
	std::string s(ss.str());
	log(s.c_str());

	cpSpaceStep(m_space, delta);
}

void PlayScene::initPhysics()
{
	m_space = cpSpaceNew();

	cpVect gravity = { 0.0f, -350.0f };
	cpSpaceSetGravity(m_space, gravity);

	cpVect beginPoint = { 0, GROUND_HEIGHT };
	cpVect endPoint = { UINT_MAX, GROUND_HEIGHT };
	m_wallBottom = cpSegmentShapeNew(cpSpaceGetStaticBody(m_space), beginPoint, endPoint, 0.0f);
	cpSpaceAddStaticShape(m_space, m_wallBottom);
}

void PlayScene::uninitPhysics()
{
	cpShapeFree(m_wallBottom);
	cpSpaceFree(m_space);
}
