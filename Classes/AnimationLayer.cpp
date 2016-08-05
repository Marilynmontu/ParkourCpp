#include "AnimationLayer.h"
#include <sstream>
#include <chipmunk.h>
#include "Global.h"

AnimationLayer * AnimationLayer::create(cpSpace *space)
{
	AnimationLayer *pRet = new(std::nothrow) AnimationLayer();
	if (pRet && (pRet->m_space = space) && pRet->init())
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
	cpShapeFree(m_shape);
	cpBodyFree(m_body);
}

bool AnimationLayer::init()
{
	if (!Layer::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("running.plist");
	m_spriteSheet = SpriteBatchNode::create("running.png");
	this->addChild(m_spriteSheet);

	Vector<SpriteFrame *> animFrames;
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "runner" << i << ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	m_runningAction = RepeatForever::create(Animate::create(animation));

	m_sprite = PhysicsSprite::createWithSpriteFrameName("runner0.png");
	auto contentSize = m_sprite->getContentSize();

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

	m_spriteSheet->addChild(m_sprite);

	m_debugNode = PhysicsDebugNode::create(m_space);
	this->addChild(m_debugNode, 10);

	// m_debugNode->setVisible(false);

	return true;
}

float AnimationLayer::getEyeX()
{
	return m_sprite->getPositionX() - RUNNER_START_X;
}
