#include "goShip.h"
#include "chipmunk\chipmunk.h"

goShip::goShip(cpSpace *space, sf::Image *img) : GameObject(space, img)
{
	_activeThruster = false;
	_thrusterMagnitude = 0.f;
	_THRUSTER_INCREMENT = 1.0f;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.
	_ROTATION_INCREMENT = 0.2f;	// arbitrary value that forward/reverse thrusters add/decrease thrusterMagnitude by.

	cpFloat radius = 60;
	cpFloat mass = 10;
  
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
	 cpShapeFree(_cpShapes[0]);
	 cpBodyFree(_body);
	_body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	cpBodySetPos(_body, cpv(400, 300));
  
	_cpShapes.pop_back();
	_cpShapes.push_back(cpSpaceAddShape(space, cpCircleShapeNew(_body, radius, cpvzero)));
	
	cpShapeSetFriction(_cpShapes[0], 0.7);
//	cpBodySetPos(_body, cpv(10, 15));
//	cpBodySetUserData(_body, this);

	// Sprite / Geometry
//	_sfShape = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
	setSpriteImage(img);
	_sprite.Resize(radius, radius);
//	_sprite.SetCenter(radius/2, radius/2);

//	_circleSprite = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
//



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
//	cpVect forceVector = cpvnormalize_safe(cpvforangle(_body->a));
//	_body->f = _body->f + forceVector;
}

void goShip::pulseThrustBack(float percentAdj) {
	_activeThruster = true;
	_thrusterMagnitude -= _THRUSTER_INCREMENT * percentAdj;
	calculateForces();
//	cpVect forceVector = -cpvnormalize_safe(cpvforangle(_body->a));
//	_body->f = _body->f + forceVector;
}

void goShip::calculateForces() {
	cpVect direction = cpvnormalize_safe(cpvforangle(_body->a));  // directional unit vector of ship
	cpVect forceVector = direction * _thrusterMagnitude;
	forceVector.y *= -1;		// reverse y axis to match sfml coordinates
	_body->f = forceVector;
}



/*

(TS) Pineapple Chunk (Indica 80/20) - 1/8oz= $47.00 1/4oz= $94.00, 1/2oz= $156.00, 1oz= $312.00   22-25%THC- 1.1% CBD New!
(TS) Trainwreck (Sativa 100) - 1/8oz =$47.00, 1/4oz=$94.00, 1/2oz=$156.00, 1oz=$312.00  New! 

	Norther lights
(TS) Northern Lights (Indica 90/10) - 1/8oz =$47.00, 1/4oz=$94.00, 1/2oz= $156.00, 1oz= $312.00   New! 

(TS) Afghan #1 (Indica 100) -1/8oz =$47.00, 1/4oz =$94.00, 1/2oz =$142.00, 1oz =$262.00   Low half left Limited 
(TS) Island Sweet Skunk (Sativa 75/25) - 1/8oz =$47.00, 1/4oz=$94.00, 1/2oz=$166.00, 1oz=$312.00 Very Low 

4 * 47 = $188

suckers x 2   ?    $18.00 OUT

dragon drops 1oz bottle = $45

$233 TOTAL

total: 251

1:30
blue ford explorer


*/