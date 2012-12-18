#include "goShip.h"


goShip::goShip(cpSpace *space, sf::Image *img) : GameObject(space, img)
{

	cpFloat radius = 60;
	cpFloat mass = 10;
  
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
	// The cpSpaceAdd*() functions return the thing that you are adding.
	//It's convenient to create and add an object in one line.
	 cpShapeFree(_cpShapes[0]);
	 cpBodyFree(_body);
	_body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	cpBodySetPos(_body, cpv(400, 300));
  
	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	_cpShapes.pop_back();
	_cpShapes.push_back(cpSpaceAddShape(space, cpCircleShapeNew(_body, radius, cpvzero)));
	
	cpShapeSetFriction(_cpShapes[0], 0.7);
//	cpBodySetPos(_body, cpv(10, 15));
//	cpBodySetUserData(_body, this);

	// Sprite / Geometry
//	_sfShape = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
	setSpriteImage(img);
	_sprite.Resize(radius*2, radius*2);
	_sprite.SetCenter(radius, radius);

//	_circleSprite = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
//
}


goShip::~goShip(void)
{
}



// Movement
void goShip::pulseRotateCW(float percentAdj) {
// cpFloat cpBodyGetTorque(const cpBody *body)
	_body->a += .2 * percentAdj;
	
	//	cpVect direction = cpvforangle(cpvtoangle(cpvrperp(cpBodyGetVel(_body)))) * percentAdj;
//	cpBodyApplyImpulse(_body, direction, cpvzero); //– Add the impulse j to body at a relative offset r from the center of gravity.
//	cpBodyApplyForce(_body, cpvzero, cpvzero);
//	_body->rot = direction;
}

void goShip::pulseRotateCCW(float percentAdj) {
	_body->a += -.5 * percentAdj;

//	cpVect direction = cpvforangle(cpvtoangle(cpvperp(cpBodyGetVel(_body)))) * percentAdj;
//	_body->rot = direction;

//	cpBodyApplyImpulse(_body, direction, cpvzero); //– Add the impulse j to body at a relative offset r from the center of gravity.
}

void goShip::pulseThrustForward(float percentAdj) {
	cpVect direction = cpvnormalize(_body->v) * percentAdj; //-cpvforangle(cpvtoangle(cpBodyGetVel(_body))) * 100 * percentAdj;
	_body->f = _body->f + direction;
//	cpBodyApplyImpulse(_body, direction, cpvzero); //– Add the impulse j to body at a relative offset r from the center of gravity.
}

void goShip::pulseThrustBack(float percentAdj) {
	cpVect direction = -cpvnormalize(_body->v) * percentAdj;
	_body->f = _body->f + direction;
//	cpBodyApplyImpulse(_body, direction, cpvzero); //– Add the impulse j to body at a relative offset r from the center of gravity.
}
