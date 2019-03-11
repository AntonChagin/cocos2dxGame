#pragma once
#include "base.h"
class Brick :
	public Base
{
public:
	virtual bool initWithSpeed(float sp, float _x);
	CREATE_FUNC(Brick);
	/** Move brick 
	* @param delta for time passed
	*/
	void act(float delta);
	/** Create brick
	* @param xy position on scene
	* @param sp speed in pixels/second
	* @param _x answer
	*/
	static Brick* Brick::create(cocos2d::Sprite* s, cocos2d::Vec2 xy, float sp, float _x);
	/** Setup dead brick
	* @param xy position on scene
	* @param sp speed in pixels/second
	* @param _x answer
	*/
	void setup(cocos2d::Vec2 xy, float sp, float _x);
	/** answer of this brick*/
	float x;
	/** speed in pixels/second*/
	float speed;
	/** is brick under floor*/
	bool dead;

	cocos2d::Label* label;
};

