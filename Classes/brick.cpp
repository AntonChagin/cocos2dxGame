#include "brick.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

USING_NS_CC;

void Brick::act(float delta)
{
	this->setPositionY(this->getPositionY()-this->speed*delta);
}

bool Brick::initWithSpeed(float sp, float _x )
{
	// 2 decimals after dot precision
	std::stringstream stream;
	stream  << std::setprecision(2) << _x;
	std::string s = stream.str();

	this->label = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 24);
	this->label->setPosition(Vec2(0,0));
	this->x = _x;
	this->addChild(this->label, 1);
	this->speed = sp;
	this->dead = false;
	return true;
}

Brick* Brick::create(cocos2d::Sprite* s, cocos2d::Vec2 xy, float sp, float _x)	
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

void Brick::setup(cocos2d::Vec2 xy, float sp, float _x)
{
	this->dead = false;
	this->setPosition(xy);
	this->x = _x;
	this->speed = sp;
	std::stringstream stream;
	stream << std::setprecision(2) << _x;
	std::string s = stream.str();
	this->label->setString(s);

}
