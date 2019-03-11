#pragma once

#include "club.h"
#include "brick.h"
#include "cocos2d.h"

class Club;
class Brick;

class MainScene : public cocos2d::Scene
{
public:
	// create and init functions
    static cocos2d::Scene* createScene();
	/** Creates MainScene
	* @param _brickSize width and height of bricks
	* @param _fieldSize width and height of field
	* @param _clubSize width and height of platform (club)
	* @return An autoreleased MainScene object.
	*/
	static MainScene* MainScene::create(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize);
    virtual bool init();
	/** Inits MainScene
	* @param _brickSize width and height of bricks
	* @param _fieldSize width and height of field
	* @param _clubSize width and height of platform (club)
	* @return An autoreleased MainScene object.
	*/
	virtual bool initWithParams(cocos2d::Vec2 _brickSize, cocos2d::Vec2 _fieldSize, cocos2d::Vec2 _clubSize);
	
	// key and touch events
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void menuCloseCallback(cocos2d::Ref* pSender);

	/** Load settings from JSON 	*/
	void MainScene::loadJsonFile();

	/** Setup game lvl according to settings and JSON 	*/
	void setup();

	/** Main game cicle 	*/
	virtual void update(float);

    CREATE_FUNC(MainScene);

	/** True if platform is dragged by mouse 	*/
	bool acting;
	int brickCount;
	float brickSpeed;
	cocos2d::Vec2 fieldSize;
	cocos2d::Vec2 brickSize;
	cocos2d::Vec2 clubSize;

private:
	/** Size of cell in pixels 	*/
	cocos2d::Vec2 cellPixelSize;

	/** Label with score 	*/
	cocos2d::Label* label;

	/** Platform 	*/
	Club* myClub;
	std::vector<Brick*> bricks;
	bool gameover;
	int score;
	int currentLvl;

	int levelsNumber;
	std::vector<std::string> problems;
	std::vector<float> rightanswers;
	std::vector<float> speeds;
	std::vector<float> points;
	std::vector<int> numberofblocks;
	std::vector<std::vector<float>> blocksX;

};
