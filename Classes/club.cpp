#include "club.h"

USING_NS_CC;

bool Club::init()
{
	if (!Base::init())
	{
		return false;
	}


	auto label = Label::createWithTTF(problem, "fonts/Marker Felt.ttf", 24);
	
	label->setPosition(Vec2(this->getChildren().front()->getBoundingBox().size.width / 2, -24));

	this->addChild(label, 2);
	return true;
}

bool Club::initWithTask(int answear, std::string sproblem)
{
	this->answ = answear;
	this->problem = sproblem;
	if (!Club::init())
	{
		return false;
	}
	return true;
}

void Club::act(Vec2 _xy)
{/*
	std::stringstream touchDetails; 
	touchDetails << "Touched at OpenGL coordinates: " <<
		_xy.x << "," << _xy.y << std::endl;
	MessageBox(touchDetails.str().c_str(), "Touched");*/
	this->setPosition(_xy);
}

Club* Club::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy, int answear, std::string sproblem)
{
	Club *base = new (std::nothrow) Club();
	if (base && base->initWithSprite(s, _xy) && base->initWithTask(answear, sproblem))
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}


bool Club::hit(int a)
{
	if (a == this->answ)
		return true;
	return false;
}
