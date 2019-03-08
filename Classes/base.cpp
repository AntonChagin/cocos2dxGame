#include "base.h"

bool Base::init()
{
	if (!cocos2d::Node::init())
	{
		return false;
	}

	return true;
}

Base* Base::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy)
{
	Base *base = new (std::nothrow) Base();
	if (base && base->initWithSprite(s,_xy))
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}



bool Base::initWithSprite(cocos2d::Sprite * s, cocos2d::Vec2 _xy = cocos2d::Vec2(0,0))
{
	if (Base::init())
	{
		this->addChild(s);
		this->setPosition(_xy);
		return true;
	}
	return false;
}

