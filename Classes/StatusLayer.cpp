#include "StatusLayer.h"

bool StatusLayer::init()
{
	if (!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	m_labelCoin = LabelTTF::create("Coins:0", "Helvetica", 20.0f);
	m_labelCoin->setColor(Color3B::BLACK);
	m_labelCoin->setPosition(70.0f, winSize.height - 20.0f);
	addChild(m_labelCoin);

	m_labelMeter = LabelTTF::create("0M", "Helvetica", 20.0f);
	m_labelMeter->setPosition(winSize.width - 70.0f, winSize.height - 20.0f);
	addChild(m_labelMeter);

	return true;
}
