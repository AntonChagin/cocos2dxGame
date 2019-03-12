#include "MainScene.h"
#include "external/json/document.h"

USING_NS_CC;

Scene* MainScene::createScene()
{    
    return MainScene::create();
}

bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	currentLvl = 0;

	loadJsonFile();

	setup();
    
    return true;
}

bool MainScene::initWithParams(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize)
{
	brickSize = _brickSize;
	fieldSize = _fieldSize;
	clubSize = _clubSize;
	return true;
}

bool intersect(Rect r1,Rect r2) {
	if (r1.intersectsRect(r2)) 
		// if rect1 right side touching rect2 left side, or vice versa
		if ((abs(r1.origin.x + r1.size.width - r2.origin.x) < 0.1) || (abs(r2.origin.x + r2.size.width - r1.origin.x) < 0.1))
			return false;
		else return true;
	
	return false;
}

void MainScene::update(float dt) {

	if (myClub->getPositionX() < 0)
	{
		myClub->stopAllActions();
		myClub->setPositionX(0);
	}else if(myClub->getPositionX() > (fieldSize.x-clubSize.x)*cellPixelSize.x)
	{
		myClub->stopAllActions();
		myClub->setPositionX((fieldSize.x - clubSize.x)*cellPixelSize.x);
	}

	for (auto &brick : bricks) 
	{
		brick->act(dt);
		// if brick is under "ground" level restart him
		if (brick->getPositionY() < -(brick->getChildren().front()->getBoundingBox().getMidY()))
		{
			brick->dead = true;
		// if brick width is odd, we need to push it left by half of cell size
			float odd = (int(round(brickSize.x)) % 2 == 0) ? 0 : (cellPixelSize.x / 2);
			// how much space is needed for platgorm to go under a brick in time
			float gap = cellPixelSize.y * (clubSize.x + brickSize.x) * brickSpeed / cellPixelSize.x + brickSize.y*cellPixelSize.y;
			brick->setup(Vec2((random<int>(brickSize.x, fieldSize.x - brickSize.x) * cellPixelSize.x - odd),
				Director::getInstance()->getVisibleSize().height + (gap))
				, brickSpeed, blocksX[currentLvl][random<int>(0, blocksX[currentLvl].size() - 1)]);
		}

		auto bounds = myClub->getChildren().front()->getBoundingBox();
		bounds.origin += myClub->getPosition();

		auto brickBounds = brick->getChildren().front()->getBoundingBox();
		brickBounds.origin += brick->getPosition();

		if (intersect(brickBounds,bounds))
			// if answer is wrong
			if (!myClub->hit(brick->x))
			{
				gameover = true;
				currentLvl = 0;
				label->setString("GAME OVER! Your score: " + std::to_string(score));
				Director::getInstance()->pause();
			}
			else {
				// if answer was right
				this->score += points[currentLvl];
				currentLvl++;
				if (currentLvl >= levelsNumber) {
					label->setString("WIN! Your score: " + std::to_string(score));
					Director::getInstance()->pause();
					return;
				}

				Director::getInstance()->pause();
				this->setup();
				Director::getInstance()->resume();
				return;
			}
	}
}


void MainScene::setup()
{
	if (currentLvl > 0) {
		bricks.clear();
		this->removeAllChildren();
	}
	else score = 0;

	gameover = false;
	brickCount = numberofblocks[currentLvl];
	brickSpeed = speeds[currentLvl];

	cellPixelSize = Vec2(Director::getInstance()->getVisibleSize().width / fieldSize.x,
		Director::getInstance()->getVisibleSize().height / fieldSize.y);

	float gap = cellPixelSize.y * (clubSize.x + brickSize.x) * brickSpeed / cellPixelSize.x + brickSize.y*cellPixelSize.y;
	int onScreenBricks = round(Director::getInstance()->getVisibleSize().height / gap) + 1;
	// spawn bricks
	for (int i = 0; i < onScreenBricks; i++)
	{
		auto sp = Sprite::create("HelloWorld.png");
		sp->setScaleX((cellPixelSize.x / sp->getContentSize().width)*brickSize.x);
		sp->setScaleY(cellPixelSize.y / (sp->getContentSize().height)*brickSize.y);
		// if brick width is odd, we need to push it left by half of cell size
		float odd = (int(round(brickSize.x)) % 2 == 0) ? 0 : (cellPixelSize.x / 2);
		auto brick = Brick::create(sp,
			Vec2((random<int>(brickSize.x, fieldSize.x - brickSize.x) * cellPixelSize.x - odd),
				Director::getInstance()->getVisibleSize().height + (gap*i))
			, brickSpeed, blocksX[currentLvl][random<int>(0, blocksX[currentLvl].size() - 1)]);
		bricks.push_back(brick);
		this->addChild(brick, 1);
	}

	// spawn platform
	auto sprite = Sprite::create("Club.png");
	sprite->setScaleX(cellPixelSize.x / (sprite->getContentSize().width)*clubSize.x);
	sprite->setScaleY(cellPixelSize.y / (sprite->getContentSize().height)*clubSize.y);
	sprite->setAnchorPoint(Vec2(0, 1));
	myClub = Club::create(sprite, Vec2(Director::getInstance()->getVisibleSize().width / 2, sprite->getContentSize().height),
		rightanswers[currentLvl], problems[currentLvl], cellPixelSize.x);
	auto touchListener = EventListenerTouchOneByOne::create();
	acting = false;
	this->addChild(myClub, 2);

	// setup touch listeners
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, myClub);

	// setup keyboard listeners
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, myClub);

	// setup label with score
	label = Label::createWithTTF("Points:" + std::to_string(score), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - label->getContentSize().height));
	this->addChild(label, 2);

	// menu with "x"
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = visibleSize.height - closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// If user launch scene after gameover, it will be paused
	if (Director::getInstance()->isPaused())
		Director::getInstance()->resume();

	if (currentLvl == 0) {

		// General Update
		this->scheduleUpdate();
	}

}

void MainScene::menuCloseCallback(Ref* pSender)
{
	// If user launch main menu scene after gameover, it will be paused

	bricks.clear();
	if (Director::getInstance()->isPaused())
		Director::getInstance()->resume();
	Director::getInstance()->popToSceneStackLevel(1);
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	int direction = 0;
	int x = round(event->getCurrentTarget()->getPositionX() / cellPixelSize.x);
	if (touch->getLocation().x > Director::getInstance()->getVisibleSize().width / 2)
		direction = 1;
	else
		direction = -1;

	int goToX = x + direction;
	if (goToX < 0 && direction < 0) goToX = 0;
	if (goToX > fieldSize.x - clubSize.x && direction > 0) goToX = fieldSize.x - clubSize.x;

	float step = goToX * cellPixelSize.x - event->getCurrentTarget()->getPositionX();
	auto moveBy = MoveBy::create(0.5, Vec2(step, 0));
	event->getCurrentTarget()->runAction(moveBy);
	return true;
}

void MainScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{	
	int direction = 0;
	int x = round(event->getCurrentTarget()->getPositionX() / cellPixelSize.x);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		direction = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		direction = 1;
		break;
	}
	
	int goToX = x + direction;
	if (goToX < 0 && direction < 0) goToX = 0;
	if (goToX > fieldSize.x - clubSize.x && direction > 0) goToX = fieldSize.x - clubSize.x;

	float step = goToX * cellPixelSize.x - event->getCurrentTarget()->getPositionX();
	auto moveBy = MoveBy::create(0.5, Vec2(step, 0));
	event->getCurrentTarget()->runAction(moveBy);
}

MainScene * MainScene::create(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize)
{
	MainScene *base = new (std::nothrow) MainScene();
	if (base && base->initWithParams(_brickSize, _fieldSize, _clubSize) && base->init())
	{
		base->autorelease();
		return base;
	}
	CC_SAFE_DELETE(base);
	return nullptr;
}


void MainScene::loadJsonFile()
{
	static int i = 0;
	static int count = 0;
	std::string id;
	rapidjson::Document document;
	std::string data = "settings.json";
	std::string content = FileUtils::getInstance()->getStringFromFile(data.c_str());
	document.Parse<0>(content.c_str());
	
	const rapidjson::Value& lvlN = document["levels"];
	assert(lvlN.IsInt());
	levelsNumber = lvlN.GetInt();

	const rapidjson::Value& arr = document["problems"];
	assert(arr.IsArray());
	for (rapidjson::SizeType i = 0; i < arr.Size(); i++) 
		problems.push_back(arr[i].GetString());

	const rapidjson::Value& arr2 = document["rightanswers"];
	assert(arr2.IsArray());
	for (rapidjson::SizeType i = 0; i < arr2.Size(); i++) 
		rightanswers.push_back(arr2[i].GetFloat());

	const rapidjson::Value& arr3 = document["speeds"];
	assert(arr3.IsArray());
	for (rapidjson::SizeType i = 0; i < arr3.Size(); i++) 
		speeds.push_back(arr3[i].GetFloat());

	const rapidjson::Value& arr4 = document["points"];
	assert(arr4.IsArray());
	for (rapidjson::SizeType i = 0; i < arr4.Size(); i++) 
		points.push_back(arr4[i].GetFloat());

	const rapidjson::Value& arr5 = document["numberofblocks"];
	assert(arr5.IsArray());
	for (rapidjson::SizeType i = 0; i < arr5.Size(); i++) 
		numberofblocks.push_back(arr5[i].GetInt());

	for (int i = 1; i <= levelsNumber; i++)
	{
		std::vector<float> tmp;
		const rapidjson::Value& arr6 = document[(std::to_string(i).c_str())];
		assert(arr6.IsArray());
		for (rapidjson::SizeType i = 0; i < arr6.Size(); i++)
			tmp.push_back(arr6[i].GetFloat());
		blocksX.push_back(tmp);
	}
	
}