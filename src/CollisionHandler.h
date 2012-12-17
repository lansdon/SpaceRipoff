#pragma once

// TO DO - Implement Base Class which is 1 set of handler functions for specific layer collisions


//
//Collision handler function types. While all of them take an arbiter, space, and a user data pointer, 
//only the begin() and preSolve() callbacks return a value. See above for more information.
//
//void cpSpaceAddCollisionHandler(
//	cpSpace *space,
//	cpCollisionType a, cpCollisionType b,
//	cpCollisionBeginFunc begin,
//	cpCollisionPreSolveFunc preSolve,
//	cpCollisionPostSolveFunc postSolve,
//	cpCollisionSeparateFunc separate,
//	void *data
//)
//
//Add a collision handler for given collision type pair. Whenever a shapes with collision type (cpShape.collision_type) 
//a and collision type b collide, these callbacks will be used to process the collision. data is a user definable context 
//pointer that is passed to each of the callbacks. NULL can be provided for callbacks you do not wish to implement, however 
//Chipmunk will call it’s own default versions for these and not the default ones you’ve set up for the space. If you need 
//to fall back on the space’s default callbacks, you’ll have to provide them individually to each handler definition.
class CollisionHandler
{
public:
	CollisionHandler(void);
	~CollisionHandler(void);

//typedef int (*cpCollisionBeginFunc)(cpArbiter *arb, struct cpSpace *space, void *data)
//typedef int (*cpCollisionPreSolveFunc)(cpArbiter *arb, cpSpace *space, void *data)
//typedef void (*cpCollisionPostSolveFunc)(cpArbiter *arb, cpSpace *space, void *data)
//typedef void (*cpCollisionSeparateFunc)(cpArbiter *arb, cpSpace *space, void *data)

	// void registerHandler(cpSpace *space);   // Helper function to register handlers
};

