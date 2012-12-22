#include "Settings.h"

Settings::Settings() :
	space(NULL),
	app(NULL),
	images(NULL),
	masterClock(NULL)
//	goManager(NULL)
{
}

Settings::Settings(cpSpace *_space, sf::RenderWindow *_app, Images *_images, sf::Clock *_msterClock) :
	space(_space),
	app(_app),
	images(_images),
	masterClock(_msterClock)
//	goManager(_goManager)
{
}

int Settings::InitializeGame(cpSpace *_space, sf::RenderWindow *_app, Images *_images, sf::Clock *_msterClock) {

	space = _space;
	app = _app;
	images = _images;
	masterClock = _msterClock;			// Master game clock -- running time
//	goManager = _goManager;	// ObjectManager

	if(!space || !app || !images || !masterClock ) return 0;
	
	return 1;
}

Settings::~Settings(void)
{
}
