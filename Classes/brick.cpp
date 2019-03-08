#include "brick.h"

USING_NS_CC;

void Brick::act(float delta)
{
	this->setPositionY(this->getPositionY()-this->speed*delta);
/*
	std::stringstream touchDetails; 
	touchDetails << "Touched at OpenGL coordinates: " <<
		_xy.x << "," << _xy.y << std::endl;
	MessageBox(touchDetails.str().c_str(), "Touched");*/
	//this->setPosition(position);
	
}

bool Brick::initWithSpeed(float sp, int _x )
{
	auto label = Label::createWithTTF(std::to_string(_x), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(0,0));
	this->x = _x;
	this->addChild(label, 1);
	this->speed = sp;
	return true;
}

void Brick::hit(Base obj)
{
}

Brick* Brick::create(cocos2d::Sprite* s, cocos2d::Vec2 xy, float sp, int _x)
	
{
	Brick *base = new (std::nothrow) Brick();
	if (base && base->initWithSprite(s, xy) && base->initWithSpeed(sp, _x))
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}
