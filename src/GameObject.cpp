#include "GameObject.h"


GameObject::GameObject(Settings *settings_ptr, sf::Image *img) :
	settings(settings_ptr),
	_space(settings_ptr->space)
{
	cpFloat radius = 10;
	cpFloat mass = 1;
  
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	_body = cpSpaceAddBody(settings->space, cpBodyNew(mass, moment));
  
	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	_cpShapes.push_back(cpSpaceAddShape(settings->space, cpCircleShapeNew(_body, radius, cpvzero)));
	cpShapeSetFriction(_cpShapes[0], 0.7);
	cpBodySetPos(_body, cpv(10, 15));
	cpBodySetUserData(_body, this);

	// Sprite / Geometry
	if(img) {
		setSpriteImage(img);
		_sprite.Resize(float(radius), float(radius));
	} else {
		_circleSprite = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
//		_sfShape = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
	}
}


GameObject::~GameObject(void)
{
	// Clean up our objects and exit!
	for(std::vector<cpShape*>::iterator it = _cpShapes.begin(); it != _cpShapes.end(); ++it) {
		cpShapeFree(*it);
	}
//	cpBodyFree(ballBody);      //Causing a crash for some reason = memory error

}

// update object state
void GameObject::update() {

	// Update sprite position to match physics body
	_sprite.SetPosition((float)cpBodyGetPos(_body).x, (float)cpBodyGetPos(_body).y);

	// Update sprite rotation to match physics body
	float angle = Utility::RAD_to_DEG(_body->a);
	if(angle > 360) angle = (int)angle % 360;	// 1-360
	if(angle < 0) angle = (int)angle % -360;	// 1-360
	_sprite.SetRotation(Utility::CP_to_SF_ANGLED(angle)); 


	// Debug
//	if(DO_DEBUG) {
//		_debug.str("");		// make private var ?
//		_debug << "Angle=" << (int)angle << std::endl;
	//	DEBUG(_debug.str());
	//	std::cerr << _debug.str() << std::endl;
//	}
}

// Load image into sprite
void GameObject::setSpriteImage(sf::Image *img) {
	_sprite.SetImage(*img);
}

sf::Sprite *GameObject::getSprite() {
//	if(_sprite.GetImage()) 
		return &_sprite;
//	else return NULL;
//	return circleSprite;
}

sf::Shape *GameObject::getShape() {
//	if(_sprite.GetImage()) 
//		return &_sprite;
//	else return NULL;
	return &_circleSprite;
}
