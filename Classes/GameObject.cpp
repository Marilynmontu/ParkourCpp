#include "GameObject.h"
#include "_chipmunk.h"

GameObject::GameObject(cpSpace * space)
	: m_mapIndex(0)
	, m_space(space)
	, m_shape(nullptr)
	, m_body(nullptr)
{
}

GameObject::~GameObject()
{
	if (m_body) {
		cpBodyFree(m_body);
		m_body = nullptr;
	}
	if (m_shape) {
		cpSpaceRemoveStaticShape(m_space, m_shape);
		cpShapeFree(m_shape);
		m_shape = nullptr;
	}
	if (m_sprite) {
		m_sprite->removeFromParent();
		m_sprite = nullptr;
	}
}

