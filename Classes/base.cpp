#include "base.h"


base::base(cocos2d::Sprite * s, cocos2d::Vec2 _xy = cocos2d::Vec2(0,0))
{
	sprite = s;
	sprite->setPosition(_xy);
}

base::~base()
{
}
