#pragma once
#include "gameobject.h"
class goShip :
	public GameObject
{
public:
	goShip(cpSpace *space, sf::Image *img);
	~goShip(void);

	// Movement
	void pulseRotateCW(float percentAdj = 1);
	void pulseRotateCCW(float percentAdj = 1);
	void pulseThrustForward(float percentAdj = 1);
	void pulseThrustBack(float percentAdj = 1);



private:


};

