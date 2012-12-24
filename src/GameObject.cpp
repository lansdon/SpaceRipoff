#include "GameObject.h"
#include "Utility.h"


GameObject::GameObject(goConfig new_config) :
	settings(new_config.settings),
	_sfShape(NULL),
	_sprite(NULL),
	_body(NULL)
{
	configureObject(new_config);

}


GameObject::~GameObject(void)
{
	// Clean up our objects and exit!
	for(std::vector<cpShape*>::iterator it = _cpShapes.begin(); it != _cpShapes.end(); ++it) {
		cpShapeFree(*it);
	}


	cpBodyFree(_body);      //Causing a crash for some reason = memory error
	delete _sprite;
	delete _sfShape;
}

// update object state
void GameObject::update() {

	if(_sprite) {
		// Update sprite position to match physics body
		_sprite->SetPosition((float)cpBodyGetPos(_body).x, (float)cpBodyGetPos(_body).y);
		_sfShape->SetPosition((float)cpBodyGetPos(_body).x, (float)cpBodyGetPos(_body).y);

		// Update sprite rotation to match physics body
		float angle = Utility::RAD_to_DEG(_body->a);
		if(angle < 0) angle = (int)angle % 360;	// 1-360
		if(angle < 0) angle = (int)angle % -360;	// 1-360
		_sprite->SetRotation(Utility::CP_to_SF_ANGLED(angle)); 
//		_sprite->SetRotation(getAngle()+0.1); 
	}

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
	if(!_sprite) {
		_sprite = new sf::Sprite();
	}
	_sprite->SetImage(*img);
}

sf::Sprite* GameObject::getSprite() {
		return _sprite;
}

sf::Shape* GameObject::getShape() {
	return _sfShape;
}


// Choose to draw sprite or geometry
void GameObject::draw() {
	if(_sprite)
		settings->app->Draw(*_sprite);
	else if(_sfShape)
		settings->app->Draw(*_sfShape);
	else{
		DEBUG("Draw error!");
	}
}



// Setup chipmunk bodies/shapes/vel/forces/position/etc
void GameObject::configureObject(goConfig config) { 
	settings = config.settings;


  	cpFloat moment = cpMomentForCircle(config.mass, 0, config.radius, cpvzero);

	if(!_body) {  
		_body = cpSpaceAddBody(settings->space, cpBodyNew(config.mass, moment));
	}
	cpBodySetMoment(_body, moment);
	cpBodySetPos(_body, config.pos);
	cpBodySetAngle(_body, config.angle);
	cpBodySetVel(_body, config.vel);
	cpBodySetForce(_body, config.force);
	
	if(!_cpShapes.size()) {		// Someday this can hold multiple shapes
		_cpShapes.push_back(cpSpaceAddShape(settings->space, cpCircleShapeNew(_body, config.radius, cpvzero)));
	}
	cpShapeSetElasticity(_cpShapes[0], 0.0);
	cpShapeSetFriction(_cpShapes[0], 0.7);

	cpBodySetUserData(_body, this);

	// Sprite / Geometry
	if(!_sprite) _sprite = new sf::Sprite();
	if(!_sfShape) _sfShape = new sf::Shape();

//	if(config.img_id) {
		_sprite->SetCenter(config.radius, config.radius);
		setSpriteImage(settings->images->getImageById(config.img_id));
		_sprite->Resize(float(config.radius*2), float(config.radius*2));
//	} else {
		*_sfShape = sf::Shape::Circle(0.0, 0.0, (float)config.radius, sf::Color(255, 255, 255)); 
//	}

		// To do - Use config.parent for collision masking

}


