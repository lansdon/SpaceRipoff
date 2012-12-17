/*
	Texture Class
		- Handles a loading of textures, keeps list of loaded files

*/

#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>


class Images
{
public:
	Images(void);
	~Images(void);
	enum image_list {IMG_NONE, IMG_SPACE_BG, IMG_2};
	image_list textureIds;

	// Returns a pointer to the sprite loaded in _sprites, requires sprite_list enum ID. 
	sf::Image *getImage(image_list id);

	// Loads sprites from vector of files mysprite.jpg (function assumes /datas/) -- set bypassHardcodedList false to load hardcoded list of sprites
	int loadImages(std::vector<std::string> *fileLocations = NULL, bool bypassHardcodedList = true);
	sf::Image loadImage(std::string fileLoc);
private:
	std::vector<sf::Image> _images;


};

