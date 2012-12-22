#include "goShip.h"
#include "chipmunk\chipmunk.h"

goShip::goShip(Settings *settings_ptr, sf::Image *img) : 
	GameObject(settings_ptr, img)
{
	_activeThruster = false;
	_thrusterMagnitude = 0.f;
	_THRUSTER_INCREMENT = 1.0f;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
	_ROTATION_INCREMENT = 0.2f;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.

	cpFloat radius = 60;
	cpFloat mass = 10;
  
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.//
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
	 cpShapeFree(_cpShapes[0]);
	 cpBodyFree(_body);
	_body = cpSpaceAddBody(_space, cpBodyNew(mass, moment));
	cpBodySetPos(_body, cpv(400, 300));
  
	_cpShapes.pop_back();
	_cpShapes.push_back(cpSpaceAddShape(settings->space, cpCircleShapeNew(_body, radius, cpvzero)));
	
	cpShapeSetFriction(_cpShapes[0], 0.7);
//	cpBodySetPos(_body, cpv(10, 15));
//	cpBodySetUserData(_body, this);

	// Sprite / Geometry
	setSpriteImage(settings->images->getImageById(settings->images->IMG_SPACESHIP));
	_sprite.Resize(radius*2, radius*2);
	_sprite.SetCenter(radius*5, radius*4);

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
	_body->f = forceVector;
}



////////////////    G-G-G-G-GUNS!!!!  ///////////////////////////////////////////

void goShip::fireBullet() {

	goBullet *pewpew = new goBullet(settings, NULL, this);

}
