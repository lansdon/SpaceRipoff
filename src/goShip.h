#pragma once
#include "gameobject.h"
#include "goBullet.h"



class goShip :
	public GameObject
{
public:
	goShip(goConfig new_config);
	virtual ~goShip(void);

	// Movement
	void pulseRotateCW(float percentAdj = 1);
	void pulseRotateCCW(float percentAdj = 1);
	void pulseThrustForward(float percentAdj = 1);
	void pulseThrustBack(float percentAdj = 1);
	float getThrusterMag() { return _thrusterMagnitude; };
	void setThrusterActive(bool bActive) { _activeThruster = bActive; if(!bActive) _thrusterMagnitude=0.0f; calculateForces(); }

	// Guns
	void fireBullet();

private:
	float _THRUSTER_INCREMENT;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
	float _ROTATION_INCREMENT;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.

	float _thrusterMagnitude;		// Represents linear velocity relative to direction the ship is facing
	bool _activeThruster;			// toggles if thrusters are active  (TEMP) This shouldl be in goShip.h

	void calculateForces(); // Applies thrusterMagnitude to ship based on current orientation.
};

