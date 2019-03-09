#pragma once
#include "base.h"

class Club :
	public Base
{
public:
	CREATE_FUNC(Club);
	int score;
	float answ;
	float step;
	std::string problem;
	virtual bool init();

	/** Inits platform with answer, problem, and step distance (when move with keyboard) */
	virtual bool initWithTask(float answer, std::string sproblem, float step);
	bool acting;
	/** set position for platform */
	void act(cocos2d::Vec2 _xy);
	/** Creates platform with answer, problem, and step distance (when move with keyboard) */
	static Club* Club::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy, int answear, std::string sproblem, float step);

	/** Check brick answer (a) with right answer */
	bool hit(float a);
};

