#include "Coin.h"
#include "_chipmunk.h"
#include "Global.h"

Coin::Coin(SpriteBatchNode * spriteSheet, cpSpace * space, cpVect pos)
	: GameObject(space)
{
	Vector<SpriteFrame *> animFrames;
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "coin" << i << ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(ss.str()));
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto action = RepeatForever::create(Animate::create(animation));

	m_sprite = PhysicsSprite::createWithSpriteFrameName("coin0.png");

	// init physics
	float radius = 0.95f * m_sprite->getContentSize().width / 2.0f;
	m_body = cpBodyNewStatic();
	cpBodySetPos(m_body, pos);
	m_sprite->setCPBody(m_body);

	m_shape = cpCircleShapeNew(m_body, radius, cpvzero);
	cpShapeSetCollisionType(m_shape, SPRITE_COIN);
	//Sensors only call collision callbacks, and never generate real collisions
	cpShapeSetSensor(m_shape, cpTrue);

	cpSpaceAddStaticShape(m_space, m_shape);

	// add sprite to sprite sheet
	m_sprite->runAction(action);
	spriteSheet->addChild(m_sprite, 1);
}
