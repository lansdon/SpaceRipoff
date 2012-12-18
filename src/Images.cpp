#include "Images.h"


Images::Images(void)
{
	loadImages(NULL, false);      // Load default hardcoded list
}


Images::~Images(void)
{
	for(std::vector<sf::Image *>::iterator it = _images.begin(); it != _images.end(); ++it) {
		delete *it;
	}
}



// Loads sprites from vector of files  /datas/mysprite.jpg -- set bypassHardcodedList false to load hardcoded list of sprites
int Images::loadImages(std::vector<std::string> *fileLocations, bool bypassHardcodedList) {
	if(!bypassHardcodedList) {
//		sf::Image *temp = loadImage("default.png");
		_images.push_back(loadImage("default.png"));
		_images.push_back(loadImage("space_bg.jpg"));
		_images.push_back(loadImage("pong/ball.png"));
		_images.push_back(loadImage("spaceship.jpg"));

		// Add more hardcoded images here
	}

	// load images from fileLocations vector
//	for(std::vector<std::string>::iterator it=fileLocations->begin(); it != fileLocations->end(); ++it) {
//		_images.push_back(loadImage(*it));
//	}
	return 0;  // todo - Error checking?
}


sf::Image *Images::loadImage(std::string fileLoc) {

	// Load the images used in the game
    sf::Image *image = new sf::Image();
    if (!image->LoadFromFile("datas/" + fileLoc)) {			// Try loading requested file
		if(!image->LoadFromFile("datas/default.png"))		// Try loading default file
			image = NULL;									// return NULL = FAIL
    }
	return image;
}
