#include "goBullet.h"


goBullet::goBullet(goConfig new_config) :	
	GameObject(new_config), //, img),
	_owner(static_cast<GameObject*>(new_config.parent)),
	_maxLinearVelocity(500)				// bullet speed
{

	//float radius = 25.0;

	//configureObject(goConfig(
	//	radius,					// radius
	//	1.f,					// mass
	//	settings->images->IMG_BALL,	// Image id
	//	cpv(250, 250),			// position
	//	0.f,					// angle
	//	cpvzero,				// velocity
	//	cpvzero));				// force


//	_sfShape = new sf::Shape();
//	_sfShape = new sf::Shape::Circle(0.0, 0.0, radius, sf::Color(255, 255, 255)); 
//	setPos(cpv(250, 250));

	//if(_owner) {
	//	cpVect direction = cpvnormalize_safe(cpvforangle(_owner->getAngle()));  // directional unit vector of ship
	//	cpVect forceVector = direction * _maxLinearVelocity;
	//	forceVector.y *= -1;		// reverse y axis to match sfml coordinates
	//	cpBodySetForce(_body, forceVector);
	//}
}


goBullet::~goBullet(void)
{
}
