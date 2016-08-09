#include "AnimationLayer.h"
#include <sstream>
#include <AudioEngine.h>
#include "StatusLayer.h"
#include "Global.h"

using namespace cocos2d::experimental; // for AudioEngine

AnimationLayer * AnimationLayer::create(cpSpace *space)
{
	AnimationLayer *pRet = new(std::nothrow) AnimationLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

AnimationLayer::~AnimationLayer()
{
#if 0
	cpShapeFree(m_shape);
	m_shape = nullptr;

	cpBodyFree(m_body);
	m_body = nullptr;
#endif
}

bool AnimationLayer::init()
{
	if (!Layer::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("running.plist");
	m_spriteSheet = SpriteBatchNode::create("running.png");
	this->addChild(m_spriteSheet);

	this->initAction();

	m_sprite = Sprite::createWithSpriteFrameName("runner0.png");
	auto contentSize = m_sprite->getContentSize();

#if 0
	m_body = cpBodyNew(1.0f, cpMomentForBox(1.0f, contentSize.width, contentSize.height));
	cpVect bodyPos = { RUNNER_START_X, GROUND_HEIGHT + contentSize.height / 2 };
	cpBodySetPos(m_body, bodyPos);

	cpVect v1 = { 150.0f, 0.0f };
	cpVect v2 = { 0.0f, 0.0f };
	cpBodyApplyImpulse(m_body, v1, v2);
	cpSpaceAddBody(m_space, m_body);

	m_shape = cpBoxShapeNew(m_body, contentSize.width - 14, contentSize.height);
	cpSpaceAddShape(m_space, m_shape);

	m_sprite->setCPBody(m_body);
	m_sprite->runAction(m_runningAction);
#endif
	m_sprite->setPosition(RUNNER_START_X, GROUND_HEIGHT + contentSize.height / 2);
	m_sprite->runAction(m_runningAction);

	auto actionTo = MoveTo::create(2.0f, Vec2(400.0f, 85.0f));
	m_sprite->runAction(actionTo);

	m_spriteSheet->addChild(m_sprite);

#if 0
	m_debugNode = PhysicsDebugNode::create(m_space);
	this->addChild(m_debugNode, 10);

	// m_debugNode->setVisible(false);
#endif

	m_stat = RUNNER_STAT_RUNNING;

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [this] (Touch *, Event *) {
		this->jump();
		// if return false, onTouchMoved, onTouchEnded, onTouchCancelled will never called.
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	auto eventListener2 = EventListenerKeyboard::create();
	eventListener2->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
			this->jump();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			Director::getInstance()->end();
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener2, this);

	this->scheduleUpdate();

	return true;
}

void AnimationLayer::update(float dt)
{
	// update meter
	auto statusLayer =
		this->getParent()->getParent()->getChildByTag<StatusLayer *>(LAYER_STATUS);
	statusLayer->updateMeter(m_sprite->getPositionX() - RUNNER_START_X);

#if 0
	// check and update runner stat
	cpVect vel = cpBodyGetVel(m_body);
	if (m_stat == RUNNER_STAT_JUMP_UP) {
		if (vel.y < 0.1f) {
			m_stat = RUNNER_STAT_JUMP_DOWN;
			m_sprite->stopAllActions();
			m_sprite->runAction(m_jumpDownAction);
		}
	}
	else if (m_stat == RUNNER_STAT_JUMP_DOWN) {
		if (vel.y == 0.0f) {
			m_stat = RUNNER_STAT_RUNNING;
			m_sprite->stopAllActions();
			m_sprite->runAction(m_runningAction);
		}
	}
#endif
}

void AnimationLayer::onExit()
{
	m_runningAction->release();
	m_jumpUpAction->release();
	m_jumpDownAction->release();

	Node::onExit();
}

float AnimationLayer::getEyeX()
{
	return m_sprite->getPositionX() - RUNNER_START_X;
}

void AnimationLayer::initAction()
{
	// init runningAction
	Vector<SpriteFrame *> animFrames;
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "runner" << i << ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	m_runningAction = RepeatForever::create(Animate::create(animation));
	m_runningAction->retain();

	// init jumpUpAction
	animFrames.clear();
	for (int i = 0; i < 4; i++) {
		std::stringstream ss;
		ss << "runnerJumpUp" << i << ".png";
		auto s = SpriteFrameCache::getInstance();
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	m_jumpUpAction = Animate::create(animation);
	m_jumpUpAction->retain();

	// init jumpDownAction
	animFrames.clear();
	for (int i = 0; i < 2; i++) {
		std::stringstream ss;
		ss << "runnerJumpDown" << i << ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	m_jumpDownAction = Animate::create(animation);
	m_jumpDownAction->retain();
}

void AnimationLayer::jump()
{
	log("jump");
	if (m_stat == RUNNER_STAT_RUNNING) {
#if 0
		cpVect j = { 0.0f, 250.0f };
		cpVect r = cpvzero;
		cpBodyApplyImpulse(m_body, j, r);
#endif
		m_stat = RUNNER_STAT_JUMP_UP;
		m_sprite->stopAllActions();
		m_sprite->runAction(m_jumpUpAction);

		AudioEngine::play2d("jump.mp3");
	}
}
