#pragma once
#include "cocos2d.h"

class base
{
public:
	base(cocos2d::Sprite* s, cocos2d::Vec2 _xy);
	~base();
	cocos2d::Sprite* sprite;
};

