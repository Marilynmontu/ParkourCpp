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

	m_gameLayer = Layer::create();

	m_gameLayer->addChild(BackgroundLayer::create(), 0, LAYER_BACKGROUND);
	m_gameLayer->addChild(AnimationLayer::create(m_space), 0, LAYER_ANIMATION);
	this->addChild(m_gameLayer);
	this->addChild(StatusLayer::create(), 0, LAYER_STATUS);

	scheduleUpdate();
}

void PlayScene::onExit()
{
	uninitPhysics();
}

void PlayScene::update(float delta)
{
	cpSpaceStep(m_space, delta);

	AnimationLayer *animationLayer =
		static_cast<AnimationLayer *>(m_gameLayer->getChildByTag(LAYER_ANIMATION));
	float eyeX = animationLayer->getEyeX();
	m_gameLayer->setPosition(-eyeX, 0.0f);
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
