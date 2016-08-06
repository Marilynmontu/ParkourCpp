#include "PlayScene.h"
#include "_chipmunk.h"
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

	m_gameLayer->addChild(BackgroundLayer::create(m_space), 0, LAYER_BACKGROUND);
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

	cpSpaceAddCollisionHandler(m_space, SPRITE_RUNNER, SPRITE_COIN, collisionCoinBegin, nullptr, nullptr, nullptr, this);
	cpSpaceAddCollisionHandler(m_space, SPRITE_RUNNER, SPRITE_ROCK, collisionRockBegin, nullptr, nullptr, nullptr, this);
}

void PlayScene::uninitPhysics()
{
	cpShapeFree(m_wallBottom);
	cpSpaceFree(m_space);
}

cpBool PlayScene::collisionCoinBegin(cpArbiter * arb, cpSpace * space, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);

	cpShape *a, *b;
	cpArbiterGetShapes(arb, &a, &b);
	cpSpaceAddPostStepCallback(This->m_space, removeCoin, b, This);

	return cpFalse;
}

cpBool PlayScene::collisionRockBegin(cpArbiter * arb, cpSpace * space, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);
	log("== game over");

	return cpFalse;
}

void PlayScene::removeCoin(cpSpace * space, void * key, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);
	BackgroundLayer *backgroundLayer =
		This->m_gameLayer->getChildByTag<BackgroundLayer *>(LAYER_BACKGROUND);
	backgroundLayer->removeObjectByShape(static_cast<cpShape *>(key));
}
