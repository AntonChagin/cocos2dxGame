#pragma once
#include "base.h"
class Brick :
	public Base
{
public:
	virtual bool initWithSpeed(float sp, int _x);
	CREATE_FUNC(Brick);
	void act(float delta);
	void hit(Base obj);
	static Brick* Brick::create(cocos2d::Sprite* s, cocos2d::Vec2 xy, float sp,int _x);

	int x;
	float speed;
	cocos2d::Vec2 position;
	bool acting;
};

