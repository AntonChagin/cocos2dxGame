#include "club.h"

USING_NS_CC;

bool Club::init()
{
	if (!Base::init())	
		return false;
	
	auto label = Label::createWithTTF(problem, "fonts/arial.ttf", 24);
	label->setPosition(Vec2(this->getChildren().front()->getBoundingBox().size.width / 2, -24));
	this->addChild(label, 2);

	return true;
}

bool Club::initWithTask(float answear, std::string sproblem, float step)
{
	this->answ = answear;
	this->problem = sproblem;
	this->step = step;

	if (!Club::init())	
		return false;

	return true;
}

void Club::act(Vec2 _xy)
{
	this->setPosition(_xy);
}

Club* Club::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy, int answear, std::string sproblem, float step)
{
	Club *base = new (std::nothrow) Club();
	if (base && base->initWithSprite(s, _xy) && base->initWithTask(answear, sproblem, step))
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}


bool Club::hit(float a)
{
	if (abs(a - this->answ) < 0.001)
		return true;
	return false;
}
