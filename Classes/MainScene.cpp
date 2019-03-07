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
	fieldSize = Vec2(10,80);

	cellPixelSize = Vec2(Director::getInstance()->getVisibleSize().width / fieldSize.x,
					Director::getInstance()->getVisibleSize().height / fieldSize.y);
    sprite = Sprite::create("HelloWorld.png");

	for (int i = 0; i < brickCount; i++)
	{
		auto sp = Sprite::create("HelloWorld.png");
		sp->setScaleX((cellPixelSize.x / sp->getContentSize().width)*brickSize.x);
		sp->setScaleY(cellPixelSize.y / (sp->getContentSize().height)*brickSize.y);
		bricks.push_back(new Brick(sp,Vec2(0, 0)));
		this->addChild(sp, 1);
	}

	for (auto &attack : bricks) // access by reference to avoid copying
	{

		attack->setup(Vec2((random<int>(1, fieldSize.x) * cellPixelSize.x), Director::getInstance()->getVisibleSize().height - (random<float>(1, cellPixelSize.x))), brickSpeed);

	}
	auto touchListener = EventListenerTouchOneByOne::create();
	acting = false;
	touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);

	myClub = new Club(sprite,Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	// increases just X scale by 2.0
	sprite->setScaleX(cellPixelSize.x/(sprite->getContentSize().width));
	
	label = Label::createWithTTF("123", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(200,100));

	// add the label as a child to this layer
	this->addChild(label, 1);
	// increases just Y scale by 2.0
	sprite->setScaleY(cellPixelSize.y / (sprite->getContentSize().height));
	sprite->setAnchorPoint(Vec2(0, 1));
	// Add a "touch" event listener to our sprite
	/*auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {

		auto bounds = event->getCurrentTarget()->getBoundingBox();

		if (bounds.containsPoint(touch->getLocation())) {
			Director::getInstance()->popScene();	
		}
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
   */
    this->addChild(sprite, 2);

	// General Update
	this->scheduleUpdate();
    
    return true;
}

void MainScene::update(float dt) {
	std::stringstream touchDetails;
	touchDetails << "coordinates: " <<
		bricks[0]->sprite->getPositionX() << "," << bricks[0]->sprite->getPositionY() << std::endl;
		label->setString(touchDetails.str().c_str());
	for (auto &attack : bricks) // access by reference to avoid copying
	{
		attack->act(dt);
		
	}
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	if (!acting) {
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		acting = (bounds.containsPoint(touch->getLocation()));
	}
	return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
	if (acting) {
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		acting = (bounds.containsPoint(touch->getLocation()));
	}
}

void MainScene::onTouchMoved(Touch* touch, Event* event)
{
	if (acting)
	{
		float x = floor(touch->getLocation().x / cellPixelSize.x);
		if (x < 0) x = 0; else if (x > fieldSize.x-1) x = fieldSize.x-1;
		x *= cellPixelSize.x;
		
		float y = floor(touch->getLocation().y / cellPixelSize.y);
		/*y++;
		if (y < 1) y = 1; else if (y > fieldSize.y) y = fieldSize.y;
		y *= cellPixelSize;*/
		y = cellPixelSize.y;
		
		myClub->act(Vec2(x,y));
	}
}
