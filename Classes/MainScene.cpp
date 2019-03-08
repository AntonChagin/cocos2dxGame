#include "MainScene.h"

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
	brickCount=5;
	brickSpeed=20;
	brickSize = Vec2(2, 2);
	fieldSize = Vec2(10,20);
	clubSize = Vec2(3,1);

	logs = "empty";
	gameover = false;

	cellPixelSize = Vec2(Director::getInstance()->getVisibleSize().width / fieldSize.x,
					Director::getInstance()->getVisibleSize().height / fieldSize.y);

	for (int i = 0; i < brickCount; i++)
	{
		auto sp = Sprite::create("HelloWorld.png");
		sp->setScaleX((cellPixelSize.x / sp->getContentSize().width)*brickSize.x);
		sp->setScaleY(cellPixelSize.y / (sp->getContentSize().height)*brickSize.y);
		auto brick = Brick::create(sp, 
			Vec2((random<int>(1, fieldSize.x) * cellPixelSize.x), Director::getInstance()->getVisibleSize().height - (random<float>(1, cellPixelSize.x)))
			, brickSpeed, random<int>(1, 10));
		bricks.push_back(brick);
		this->addChild(brick, 1);
	}


    sprite = Sprite::create("HelloWorld.png");

	sprite->setScaleX(cellPixelSize.x/(sprite->getContentSize().width)*clubSize.x);
	sprite->setScaleY(cellPixelSize.y / (sprite->getContentSize().height)*clubSize.y);
	sprite->setAnchorPoint(Vec2(0, 1));

	myClub = Club::create(sprite,Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2),
		10,"5+x=15");
	
	auto touchListener = EventListenerTouchOneByOne::create();
	acting = false;
	touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, myClub);
    this->addChild(myClub, 2);

	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);

	label->setPosition(Vec2(100, 200));

	this->addChild(label, 2);
	
	// General Update
	this->scheduleUpdate();
    
    return true;
}

void MainScene::update(float dt) {
	/*std::stringstream touchDetails;
	touchDetails << "coordinates: " <<
		acting << ", " << logs;// bricks[0]->getPositionY() << std::endl;
		label->setString(touchDetails.str().c_str());*/
	for (auto &attack : bricks) // access by reference to avoid copying
	{
		attack->act(dt);
		auto bounds = myClub->getChildren().front()->getBoundingBox();
		bounds.origin += myClub->getPosition();
		if (bounds.intersectsRect(attack->getBoundingBox()))
			gameover=!myClub->hit(attack->x);
	}
	if (gameover) { logs = "GAME OVER"; 
	label->setString(logs);
	}

}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	if (!acting) {
		auto bounds = event->getCurrentTarget()->getChildren().front()->getBoundingBox();
		bounds.origin += event->getCurrentTarget()->getPosition();
		acting = (bounds.containsPoint(touch->getLocation()));
	}
	return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
	if (acting) {
		auto bounds = event->getCurrentTarget()->getChildren().front()->getBoundingBox();
		bounds.origin += event->getCurrentTarget()->getPosition();
		acting = (bounds.containsPoint(touch->getLocation()));
	}
}

void MainScene::onTouchMoved(Touch* touch, Event* event)
{
	if (acting)
	{
		float x = floor(touch->getLocation().x / cellPixelSize.x);
		if (x < 0) x = 0; else if (x > fieldSize.x-clubSize.x) x = fieldSize.x-1;
		x *= cellPixelSize.x;
		
		float y = floor(touch->getLocation().y / cellPixelSize.y);
		/*y++;
		if (y < 1) y = 1; else if (y > fieldSize.y) y = fieldSize.y;
		y *= cellPixelSize;*/
		y = cellPixelSize.y;
		
		myClub->act(Vec2(x,y));
	}
}
