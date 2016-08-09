#include "PlayScene.h"
#include <AudioEngine.h>
#include "BackgroundLayer.h"
#include "AnimationLayer.h"
#include "StatusLayer.h"
#include "GameOverLayer.h"
#include "Global.h"

#include <string>
#include <sstream>

using namespace cocos2d::experimental; // for AudioEngine

void PlayScene::onEnter()
{
	Node::onEnter();
	initPhysics();
	
	m_gameLayer = Layer::create();

	m_gameLayer->addChild(BackgroundLayer::create(nullptr), 0, LAYER_BACKGROUND);
	m_gameLayer->addChild(AnimationLayer::create(nullptr), 0, LAYER_ANIMATION);
	this->addChild(m_gameLayer);
	this->addChild(StatusLayer::create(), 0, LAYER_STATUS);

	AudioEngine::play2d("background.mp3", true);

	this->scheduleUpdate();
}

void PlayScene::onExit()
{
	// GameLayer will destruct by cocos2d after this function (who 
	// destroy cpSpace). The destruction still needs cpSpace. So
	// do it in advance.
	m_gameLayer->removeFromParentAndCleanup(true);
	uninitPhysics();

	// [FIXED]
	// call parent onExit()
	// otherwise update() will still be called after this function
	Node::onExit();
}

void PlayScene::update(float delta)
{
//	cpSpaceStep(m_space, delta);

	AnimationLayer *animationLayer =
		static_cast<AnimationLayer *>(m_gameLayer->getChildByTag(LAYER_ANIMATION));
	float eyeX = animationLayer->getEyeX();
	m_gameLayer->setPosition(-eyeX, 0.0f);
}

void PlayScene::initPhysics()
{
#if 0
	m_space = cpSpaceNew();

	cpVect gravity = { 0.0f, -350.0f };
	cpSpaceSetGravity(m_space, gravity);

	cpVect beginPoint = { 0, GROUND_HEIGHT };
	cpVect endPoint = { UINT_MAX, GROUND_HEIGHT };
	m_wallBottom = cpSegmentShapeNew(cpSpaceGetStaticBody(m_space), beginPoint, endPoint, 0.0f);
	cpSpaceAddStaticShape(m_space, m_wallBottom);

	cpSpaceAddCollisionHandler(m_space, SPRITE_RUNNER, SPRITE_COIN, collisionCoinBegin, nullptr, nullptr, nullptr, this);
	cpSpaceAddCollisionHandler(m_space, SPRITE_RUNNER, SPRITE_ROCK, collisionRockBegin, nullptr, nullptr, nullptr, this);
#endif
}

void PlayScene::uninitPhysics()
{
#if 0
	cpShapeFree(m_wallBottom);
	m_wallBottom = nullptr;

	cpSpaceFree(m_space);
	m_space = nullptr;
#endif
}

#if 0
cpBool PlayScene::collisionCoinBegin(cpArbiter * arb, cpSpace * space, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);

	cpShape *a, *b;
	cpArbiterGetShapes(arb, &a, &b);
	cpSpaceAddPostStepCallback(This->m_space, removeCoin, b, This);

	AudioEngine::play2d("pickup_coin.mp3");

	auto statusLayer = This->getChildByTag<StatusLayer *>(LAYER_STATUS);
	statusLayer->addCoin(1);

	return cpFalse;
}

cpBool PlayScene::collisionRockBegin(cpArbiter * arb, cpSpace * space, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);
	log("== game over");

	AudioEngine::stopAll();

	Director::getInstance()->pause();
	This->addChild(GameOverLayer::create());

	return cpFalse;
}
#endif

void PlayScene::removeCoin(cpSpace * space, void * key, void * data)
{
	PlayScene *This = static_cast<PlayScene *>(data);
	BackgroundLayer *backgroundLayer =
		This->m_gameLayer->getChildByTag<BackgroundLayer *>(LAYER_BACKGROUND);
//	backgroundLayer->removeObjectByShape(static_cast<cpShape *>(key));
}
