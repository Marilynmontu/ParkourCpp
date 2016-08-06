#pragma once

#include "GameObject.h"

class Rock : public GameObject
{
public:
	Rock(SpriteBatchNode *spriteSheet, cpSpace *space, float posX);
};
