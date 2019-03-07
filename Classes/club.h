#pragma once
#include "base.h"
class Club :
	public base
{
public:
	Club(cocos2d::Sprite* s, cocos2d::Vec2 _xy);
	~Club();
	int score;
	bool acting;
	void act(cocos2d::Vec2 _xy);
	void hit(base obj);
};

