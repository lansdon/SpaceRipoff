#include "Images.h"


Images::Images(void)
{
}


Images::~Images(void)
{
}



// Loads sprites from vector of files  /datas/mysprite.jpg -- set bypassHardcodedList false to load hardcoded list of sprites
int Images::loadImages(std::vector<std::string> *fileLocations, bool bypassHardcodedList) {
	if(!bypassHardcodedList) {
//		_images.push_back(loadImage("datas/default.gif"));
//		_images.push_back(loadImage("datas/space_bg.gif"));

		// Add more hardcoded images here
	}

	// load images from fileLocations vector
	for(std::vector<std::string>::iterator it=fileLocations->begin(); it != fileLocations->end(); ++it) {
//		_images.push_back(loadImage(*it));
	}
	return 0;  // todo - Error checking?
}


sf::Image loadImage(std::string fileLoc) {

	// Load the images used in the game
    sf::Image image;
    if (!image.LoadFromFile("datas/" + fileLoc)) {
		image.LoadFromFile("datas/default.gif");
    }
	return image;
}
