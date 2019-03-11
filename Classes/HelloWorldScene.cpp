#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include <ui/UITextField.h>
#include <ui/UIButton.h>
#include <ui/cocosGUI.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	// constants to align ui elements
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 startPosTextFields = Vec2(origin.x + visibleSize.width / 2, 100);

	// sizes by default
	brickSize = Vec2(2, 2);
	fieldSize = Vec2(10, 20);
	clubSize = Vec2(3, 1);
	float fieldsDefault[6] = { fieldSize.x,fieldSize.y,clubSize.x,clubSize.y, brickSize.x,brickSize.y };

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
		float y = visibleSize.height - closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	// create ui for game settings: "FieldW", "FieldH", "PlatformW", "PlatformH", "BlockW", "BlockH"
	for (int i = 0; i < 6; i++)
	{
		auto label = Label::createWithSystemFont(nameOfFields[i], "Arial", 24);
		label->setPosition(Vec2(startPosTextFields.x, startPosTextFields.y + i * 30));
		this->addChild(label);
		auto field = ui::TextField::create(std::to_string(fieldsDefault[i]), "Arial", 24);
		field->setString(std::to_string(fieldsDefault[i]));
		field->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + i * 30));
		this->addChild(field);
		TextFields.push_back(field);
	}

	// apply and start button
	auto button = ui::Button::create("button.png", "button.png", "button.png");
	button->setTitleText("Apply and start");
	button->setTitleFontSize(24);
	button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::newGameCallback, this)); 
	button->setPosition(Vec2(startPosTextFields.x, startPosTextFields.y+30*8));
	this->addChild(button);

    auto label = Label::createWithTTF("Prototype game", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void HelloWorld::newGameCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	std::vector<float> fieldArg; 
	try {
		for (auto &field : TextFields)		
			fieldArg.push_back(std::stoi(field->getString()));		
	}
	catch (std::invalid_argument e1) {
		MessageBox("Invalid input!", "Warning");
		return;
	}
	//std::string  nameOfFields[6] = { "FieldW", "FieldH", "PlatformW", "PlatformH", "BlockW", "BlockH" };
	
	auto myScene = MainScene::create(Vec2(fieldArg[4], fieldArg[5]), Vec2(fieldArg[0], fieldArg[1]), Vec2(fieldArg[2], fieldArg[3]));
	
	Director::getInstance()->pushScene(myScene);
}