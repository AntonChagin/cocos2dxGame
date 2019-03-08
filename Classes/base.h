#pragma once
#include "cocos2d.h"
/** @class Base
* @brief Base �������� Node
������������ ��� ������� ����� ��� ���� ��������� � ���� (���������, �����)
*/
class Base :
	public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool initWithSprite(cocos2d::Sprite* s, cocos2d::Vec2 _xy);
	/** ������� ������� ������.
	* @param s ������ � ������� ���������������� ������.
	* @param _xy ��������� Base ������� �� �����
	* @return An autoreleased Base object.
	*/
	static Base* Base::create(cocos2d::Sprite * s, cocos2d::Vec2 _xy);
	CREATE_FUNC(Base);
};

