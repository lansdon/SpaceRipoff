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
	float getThrusterMag() { return _thrusterMagnitude; };


private:

	bool _activeThruster;			// toggles if thrusters are active
	float _thrusterMagnitude;		// Represents linear velocity relative to direction the ship is facing
	void calculateForces(); // Applies thrusterMagnitude to ship based on current orientation.
	float _THRUSTER_INCREMENT;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
	float _ROTATION_INCREMENT;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
};

