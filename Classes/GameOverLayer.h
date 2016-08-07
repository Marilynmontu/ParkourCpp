#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public LayerColor
{
public:
	CREATE_FUNC(GameOverLayer);
	bool init() override;

protected:
	void onRestart(Ref *);
};
