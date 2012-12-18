
/*
	GameObject Base Class
	todo - everything
*/
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "config.h"
#include "chipmunk\chipmunk.h"



class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	void update(); // update object state


	// To do - Chipmunk Wrapper

private:
	sf::Sprite _sprite;		// Sprite 
	cpBody *_body;			// Chipmunk body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	std::vector<cpShape*> _shapes; // chipmunk shapes = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));

};
  
