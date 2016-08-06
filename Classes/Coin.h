#pragma once

#include "GameObject.h"

struct cpVect;
class Coin : public GameObject
{
public:
	Coin(SpriteBatchNode *spriteSheet, cpSpace *space, cpVect pos);
};
