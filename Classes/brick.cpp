#include "brick.h"

USING_NS_CC;


Brick::Brick(Sprite* s, Vec2 xy):base(s, xy)
{

	// Add a "touch" event listener to our sprite
	
}


Brick::~Brick()
{
}

void Brick::act(float delta)
{
	position.y -= speed*delta;
/*
	std::stringstream touchDetails; 
	touchDetails << "Touched at OpenGL coordinates: " <<
		_xy.x << "," << _xy.y << std::endl;
	MessageBox(touchDetails.str().c_str(), "Touched");*/
	sprite->setPosition(position);
	
}


void Brick::hit(base obj)
{
}

void Brick::setup(Vec2 xy, float sp)
{
	speed = sp;
	sprite->setPosition(xy);

	position = xy;
}
