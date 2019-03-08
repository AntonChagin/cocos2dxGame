#pragma once

#include "club.h"
#include "brick.h"
#include "cocos2d.h"

class Club;
class Brick;

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual bool initWithParams(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize);
	bool acting;
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);

	static MainScene* MainScene::create(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize);

    CREATE_FUNC(MainScene);
	cocos2d::Vec2 fieldSize;
	int brickCount;
	float brickSpeed;
	cocos2d::Vec2 brickSize;
	cocos2d::Vec2 clubSize;
	std::string logs;
	virtual void update(float);

private:
	cocos2d::Vec2 cellPixelSize;
	cocos2d::Label* label;
	cocos2d::Sprite* sprite;
	Club* myClub;
	std::vector<Brick*> bricks;
	bool gameover;
	int score;
};
