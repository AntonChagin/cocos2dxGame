#pragma once
#include "base.h"
class Brick :
	public base
{
public:
	Brick(cocos2d::Sprite* s, cocos2d::Vec2 xy);
	~Brick();
	cocos2d::Vec2 position;
	float speed;
	bool acting;
	void act(float delta);
	void hit(base obj);
	void setup(cocos2d::Vec2 xy, float sp);
};

