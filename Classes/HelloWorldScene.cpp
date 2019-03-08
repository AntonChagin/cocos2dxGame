/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 startPosTextFields = Vec2(origin.x + visibleSize.width / 2, 100);
	brickSize = Vec2(2, 2);
	fieldSize = Vec2(10, 20);
	clubSize = Vec2(3, 1);

	int fieldsDefault[6] = { fieldSize.x,fieldSize.y,clubSize.x,clubSize.y, brickSize.x,brickSize.y };
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

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
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	// менять размер поля, платформы, размера и количества блоков, скорости игры 
	//а также задавать в файле математические выражения для каждого раунда с указанием количества выпадающих блоков и чисел на них.

	for (int i = 0; i < 6; i++)
	{
		auto label = Label::createWithSystemFont(nameOfFields[i], "Arial", 24);
		label->setPosition(Vec2(startPosTextFields.x, startPosTextFields.y + i * 30));		
		this->addChild(label);
	}
	FieldW = ui::TextField::create(std::to_string(fieldsDefault[0]), "Arial", 24);
	FieldW->setString(std::to_string(fieldsDefault[0]));
	FieldW->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 0 * 30));
	this->addChild(FieldW);
	FieldH = ui::TextField::create(std::to_string(fieldsDefault[1]), "Arial", 24);
	FieldH->setString(std::to_string(fieldsDefault[1]));
	FieldH->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 1 * 30));
	this->addChild(FieldH);
	PlatformW = ui::TextField::create(std::to_string(fieldsDefault[2]), "Arial", 24);
	PlatformW->setString(std::to_string(fieldsDefault[2]));
	PlatformW->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 2 * 30));
	this->addChild(PlatformW);
	PlatformH = ui::TextField::create(std::to_string(fieldsDefault[3]), "Arial", 24);
	PlatformH->setString(std::to_string(fieldsDefault[3]));
	PlatformH->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 3 * 30));
	this->addChild(PlatformH);
	BlockW = ui::TextField::create(std::to_string(fieldsDefault[4]), "Arial", 24);
	BlockW->setString(std::to_string(fieldsDefault[4]));
	BlockW->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 4 * 30));
	this->addChild(BlockW);
	BlockH = ui::TextField::create(std::to_string(fieldsDefault[5]), "Arial", 24);
	BlockH->setString(std::to_string(fieldsDefault[5]));
	BlockH->setPosition(Vec2(startPosTextFields.x + 100, startPosTextFields.y + 5 * 30));
	this->addChild(BlockH);


	auto button = ui::Button::create("button.png", "button.png", "button.png");

	button->setTitleText("Apply and start");
	button->setTitleFontSize(24);
	button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::newGameCallback, this)); // obviously use your own callback and scene here.
	button->setPosition(Vec2(startPosTextFields.x, startPosTextFields.y+30*8));
	this->addChild(button);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
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
	/*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::newGameCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{

	//std::string  nameOfFields[6] = { "FieldW", "FieldH", "PlatformW", "PlatformH", "BlockW", "BlockH" }; 
	try {
		// protected code
	brickSize.x = std::stoi(BlockW->getString());
	brickSize.y = std::stoi(BlockH->getString());
	fieldSize.x = std::stoi(FieldW->getString());
	fieldSize.y = std::stoi(FieldH->getString());
	clubSize.x = std::stoi(PlatformW->getString());
	clubSize.y = std::stoi(PlatformH->getString());
	}
	catch (std::invalid_argument e1) {
		// catch block
		MessageBox("Invalid input!", "Warning");
		return;
	}
	
	auto myScene = MainScene::create(brickSize, fieldSize, clubSize);
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->pushScene(myScene);

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}