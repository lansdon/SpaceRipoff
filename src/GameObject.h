
/*
	GameObject Base Class
	todo - everything
*/
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>



class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	// To do - Chipmunk Wrapper

private:
	sf::Sprite _sprite;		// Sprite 

};
  
