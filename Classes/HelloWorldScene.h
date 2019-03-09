#include "cocos2d.h"
#include <ui/cocosGUI.h>

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	//close game
    void menuCloseCallback(cocos2d::Ref* pSender);
	//apply changes and start new game
	void HelloWorld::newGameCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    CREATE_FUNC(HelloWorld);

private:
	//Vectors to keep dimensions of playfield, platform and blocks
	cocos2d::Vec2 brickSize;
	cocos2d::Vec2 fieldSize;
	cocos2d::Vec2 clubSize;

	//TextFields for input dimensions of playfield, platform and blocks
	std::vector<cocos2d::ui::TextField*> TextFields;
	cocos2d::ui::TextField* FieldW;
	cocos2d::ui::TextField* FieldH;
	cocos2d::ui::TextField* PlatformW;
	cocos2d::ui::TextField* PlatformH;
	cocos2d::ui::TextField* BlockW;
	cocos2d::ui::TextField* BlockH;

	//names for iteration over textfields ui representation
	std::string  nameOfFields[6] = { "FieldW", "FieldH", "PlatformW", "PlatformH", "BlockW", "BlockH" };
};
