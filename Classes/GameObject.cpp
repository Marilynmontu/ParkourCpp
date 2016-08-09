#include "GameObject.h"

GameObject::GameObject(cpSpace * space)
	: m_mapIndex(0)
{
}

GameObject::~GameObject()
{
#if 0
	if (m_body) {
		cpBodyFree(m_body);
		m_body = nullptr;
	}
	if (m_shape) {
		cpSpaceRemoveStaticShape(m_space, m_shape);
		cpShapeFree(m_shape);
		m_shape = nullptr;
	}
#endif

	if (m_sprite) {
		m_sprite->removeFromParent();
		m_sprite = nullptr;
	}
}

