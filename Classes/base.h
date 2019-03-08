#pragma once
#include "cocos2d.h"
/** @class Base
* @brief Base подкласс Node
Используется как базовый класс для всех сущностей в игре (платформа, блоки)
*/
class Base :
	public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool initWithSprite(cocos2d::Sprite* s, cocos2d::Vec2 _xy);
	/** Создает базовый объект.
	* @param s спрайт с которым инициализируется объект.
	* @param _xy положение Base объекта на сцене
	* @return An autoreleased Base object.
	*/
	static Base* Base::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy);
	CREATE_FUNC(Base);
};

