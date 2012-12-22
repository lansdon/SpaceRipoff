#pragma once

#include "chipmunk\chipmunk.h"
#include "SFML\Graphics.hpp"
#include "Images.h"
//#include "GameObjectManager.h"

class Settings
{
public:
	Settings();
	Settings(cpSpace *_space, 
		sf::RenderWindow *_app, 
		Images *_images, 
		sf::Clock *_masterClock);

	~Settings(void);

	int InitializeGame(cpSpace *_space, sf::RenderWindow *_app, Images *_images, sf::Clock *_msterClock);

	// References to common data
	cpSpace *space;
	sf::RenderWindow *app;
	Images *images;
	sf::Clock *masterClock;			// Master game clock -- running time
//	GameObjectManager *goManager;	// ObjectManager

	// Enum zone
	enum object_type { OBJ_NONE, OBJ_SHIP, OBJ_BULLET } objType;
//	enum image_list { IMG_NONE, IMG_SPACE_BG, IMG_BALL, IMG_SPACESHIP } imageList;


};

