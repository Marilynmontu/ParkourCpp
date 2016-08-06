#include "Rock.h"
#include "_chipmunk.h"
#include "Global.h"

Rock::Rock(SpriteBatchNode * spriteSheet, cpSpace * space, float posX)
	: GameObject(space)
{
	m_sprite = PhysicsSprite::createWithSpriteFrameName("rock.png");

	m_body = cpBodyNewStatic();
	cpVect pos;
	pos.x = posX;
	pos.y = m_sprite->getContentSize().height / 2.0f + GROUND_HEIGHT;
	cpBodySetPos(m_body, pos);
	m_sprite->setCPBody(m_body);

	auto size = m_sprite->getContentSize();
	m_shape = cpBoxShapeNew(m_body, size.width, size.height);
	cpShapeSetCollisionType(m_shape, SPRITE_ROCK);

	cpSpaceAddStaticShape(m_space, m_shape);
	spriteSheet->addChild(m_sprite);
}
