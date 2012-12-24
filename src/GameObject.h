
/*
	GameObject Base Class

	Derived classes:(TBD) circle? line? 
	todo - everything
*/
#pragma once
// SFML / Chipmunk
#include "chipmunk\chipmunk.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

// STL
#include <sstream>
#include <iostream>

// Space Junk
#include "debug.h"
#include "Settings.h"


struct goConfig {
	goConfig(float new_radius=10,float new_mass=1,Images::image_list new_img_id=Images::IMG_BALL,cpVect new_pos=cpvzero,float new_angle=0,cpVect new_vel=cpvzero,cpVect new_force=cpvzero, Settings* new_settings=NULL, void* new_parent=NULL) : 
		radius(new_radius),mass(new_mass),img_id(new_img_id),pos(new_pos),angle(new_angle),vel(new_vel),force(new_force), settings(new_settings), parent(new_parent) {};

	float radius;
	float mass;
	Images::image_list img_id;
	cpVect pos;
	float angle;
	cpVect vel;
	cpVect force;
	Settings* settings;
	void* parent;
};


class GameObject
{
public:

	GameObject(goConfig new_config);
	virtual ~GameObject(void);



	void update(); // update object state

	void setSpriteImage(sf::Image* img);			// Load image into sprite
	sf::Sprite* getSprite();
	sf::Shape* getShape();   // = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
	void draw();
	// 


	// To do - Chipmunk Wrapper
	cpVect getPos() { return cpBodyGetPos(_body); };
	cpVect getVel() { return cpBodyGetVel(_body); };
	cpVect getForce() { return (_body ? _body->f : cpvzero); };
	cpFloat getAngle() { return (_body ? _body->a : 0.0f); };
	cpFloat getWidth() { return _cpShapes[0]->bb.b; }
	cpShape* getFirstShape() { return _cpShapes[0]; }

	void setPos(cpVect pos) { cpBodySetPos(_body, pos); };
	void setVel(cpVect vel) { cpBodySetVel(_body, vel); };
	void setForce(cpVect force) { if(_body) cpBodyApplyForce(_body, force, cpvzero); };
	void setAngle(cpFloat theta_rads) { if(_body) cpBodySetAngle(_body, theta_rads); };


protected:
	Settings* settings;

	sf::Sprite* _sprite;				// Sprite 
	cpBody* _body;						// Chipmunk body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	std::vector<cpShape*> _cpShapes;	// chipmunk shapes = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	sf::Shape* _sfShape;				// optional draw method using geometry instead of sprites. (should be derived class?)

	void configureObject(goConfig config);  // Setup chipmunk bodies/shapes/vel/forces/position/etc

	// debug
	std::stringstream _debug;			

};
  
