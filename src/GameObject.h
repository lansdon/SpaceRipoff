
/*
	GameObject Base Class

	Derived classes:(TBD) circle? line? 
	todo - everything
*/
#pragma once
// SFML / Chipmunk
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

// STL
#include <sstream>
#include <iostream>

// Space Junk
#include "config.h"
#include "chipmunk\chipmunk.h"
//#include "Images.h"
#include "Utility.h"
#include "debug.h"
#include "Settings.h"


class GameObject
{
public:

	GameObject(Settings *settings_ptr, sf::Image *img = NULL);
	~GameObject(void);

	void update(); // update object state

	void setSpriteImage(sf::Image *img);			// Load image into sprite
	sf::Sprite *getSprite();
	sf::Shape *getShape();   // = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 

	// 


	// To do - Chipmunk Wrapper
	cpVect getPos() { return cpBodyGetPos(_body); };
	cpVect getVel() { return cpBodyGetVel(_body); };
	cpVect getForce() { return _body->f; };
	cpFloat getAngle() { return _body->a; };

protected:
	Settings *settings;
	sf::Sprite _sprite;				// Sprite 
	cpBody *_body;					// Chipmunk body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	std::vector<cpShape*> _cpShapes; // chipmunk shapes = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	cpSpace *_space;				// Reference to cp Space
	sf::Shape _sfShape;				// optional draw method using geometry instead of sprites. (should be derived class!)
	sf::Shape _circleSprite; // = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 


	// debug
	std::stringstream _debug;		// make private var ?

};
  
