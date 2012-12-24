#include "goShip.h"
#include "chipmunk\chipmunk.h"
#include "GameObjectManager.h"

goShip::goShip(goConfig new_config) : 
	GameObject(new_config),
	_activeThruster(false),
	_thrusterMagnitude(0.f),
	_THRUSTER_INCREMENT(1.0f),	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
	_ROTATION_INCREMENT(0.2f)	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.

{
//	_sprite->Resize((float)new_config.radius, (float)new_config.radius);
//	_sprite->SetCenter((float)new_config.radius/2, (float)new_config.radius/2);

}


goShip::~goShip(void)
{
}



// Movement
void goShip::pulseRotateCW(float percentAdj) {
	_activeThruster = true;
	cpBodySetAngle(_body, _body->a - _ROTATION_INCREMENT * percentAdj);
	calculateForces();
}

void goShip::pulseRotateCCW(float percentAdj) {
	_activeThruster = true;
	cpBodySetAngle(_body, _body->a + _ROTATION_INCREMENT * percentAdj);
	calculateForces();
}

void goShip::pulseThrustForward(float percentAdj) {
	_activeThruster = true;
	_thrusterMagnitude += _THRUSTER_INCREMENT * percentAdj;
	calculateForces();
}

void goShip::pulseThrustBack(float percentAdj) {
	_activeThruster = true;
	_thrusterMagnitude -= _THRUSTER_INCREMENT * percentAdj;
	calculateForces();
}

void goShip::calculateForces() {
	cpVect direction = cpvnormalize_safe(cpvforangle(_body->a));  // directional unit vector of ship
	cpVect forceVector = direction * _thrusterMagnitude;
	forceVector.y *= -1;		// reverse y axis to match sfml coordinates
	cpBodySetForce(_body, forceVector);
//	_body->f = forceVector;
}



////////////////    G-G-G-G-GUNS!!!!  ///////////////////////////////////////////

void goShip::fireBullet() {
	
	cpVect direction = cpvnormalize_safe(cpvforangle(_body->a));  // directional unit vector of ship
	cpVect forceVector = direction * 200.0;
	forceVector.y *= -1;		// reverse y axis to match sfml coordinates
	
	GameObjectManager::getInstance(settings)->createBullet(goConfig(
		15.f,				// radius
		1.0f,				// mass
		Images::IMG_BALL,	// Image id
		getPos() + (direction* (_sprite->GetSize().x/2)),		// position
		getAngle(),				// angle
		forceVector,			// velocity
		cpvzero,			// force
		settings,			// settings
		this));			// owner/shooter

}
