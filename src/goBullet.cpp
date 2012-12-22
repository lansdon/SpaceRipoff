#include "goBullet.h"


goBullet::goBullet(Settings *settings_ptr, sf::Image *img, GameObject *shooter) :	
	GameObject(settings_ptr), //, img),
	_owner(shooter),
	_maxLinearVelocity(50)				// bullet speed
{

	float radius = 10.0;


	_circleSprite = sf::Shape::Circle(0.0, 0.0, radius, sf::Color(255, 255, 255)); 


	cpVect direction = cpvnormalize_safe(cpvforangle(_owner->getAngle()));  // directional unit vector of ship
	cpVect forceVector = direction * _maxLinearVelocity;
	forceVector.y *= -1;		// reverse y axis to match sfml coordinates
	_body->f = forceVector;
}


goBullet::~goBullet(void)
{
}
