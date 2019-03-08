#pragma once
#include "base.h"
class Club :
	public Base
{
public:
	CREATE_FUNC(Club);
	int score;
	int answ;
	std::string problem;
	virtual bool init();
	virtual bool initWithTask(int answear, std::string sproblem);
	bool acting;
	void act(cocos2d::Vec2 _xy);
	static Club* Club::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy, int answear, std::string sproblem);
	bool hit(int a);
};

