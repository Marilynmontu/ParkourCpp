#pragma once

#include "cocos2d.h"

USING_NS_CC;

class StatusLayer : public Layer
{
public:
	bool init() override;

	CREATE_FUNC(StatusLayer);

	void updateMeter(float px);
	void addCoin(int num);

protected:
	LabelTTF *m_labelCoin;
	LabelTTF *m_labelMeter;
	int m_coins;
};

