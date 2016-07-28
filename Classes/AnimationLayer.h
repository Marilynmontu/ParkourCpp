#pragma once

#include "cocos2d.h"

USING_NS_CC;

class AnimationLayer : public Layer
{
public:
	bool init() override;

	CREATE_FUNC(AnimationLayer);

protected:
	SpriteBatchNode *m_spriteSheet;
	Action *m_runningAction;
	Sprite *m_sprite;

};
