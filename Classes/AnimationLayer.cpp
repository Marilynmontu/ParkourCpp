#include "AnimationLayer.h"
#include <sstream>

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
	m_sprite = Sprite::createWithSpriteFrameName("runner0.png");
	m_sprite->setPosition(80.0f, 85.0f);
	m_sprite->runAction(m_runningAction);
	m_spriteSheet->addChild(m_sprite);

	return true;
}
