#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:
	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(MenuScene);

protected:
	void onPlay(Ref *);
};

