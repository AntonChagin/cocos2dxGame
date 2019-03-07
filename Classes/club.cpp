#include "club.h"

USING_NS_CC;


Club::Club(Sprite* s, Vec2 _xy):base(s, _xy)
{

	// Add a "touch" event listener to our sprite
	
}


Club::~Club()
{
}

void Club::act(Vec2 _xy)
{/*
	std::stringstream touchDetails; 
	touchDetails << "Touched at OpenGL coordinates: " <<
		_xy.x << "," << _xy.y << std::endl;
	MessageBox(touchDetails.str().c_str(), "Touched");*/
	sprite->setPosition(_xy);
}


void Club::hit(base obj)
{
}
