#pragma once
#include "cocos2d.h"
/** @class Base
* @brief Base subclass Node
*/
class Base :
	public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool initWithSprite(cocos2d::Sprite* s, cocos2d::Vec2 _xy);
	/** Creates base object.
	* @param s sprite for init.
	* @param _xy position of Base object on scene
	* @return An autoreleased Base object.
	*/
	static Base* Base::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy);
	CREATE_FUNC(Base);
};

