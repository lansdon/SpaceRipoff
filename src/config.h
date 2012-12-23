/*
	Configuration settings


*/

#ifndef CONFIG_H
#define CONFIG_H
#include <chipmunk\chipmunk.h>

#define TITLE "Space Ripoff"

// Initial resolution 
#define START_RESOLUTION_X 800
#define START_RESOLUTION_Y 600
#define START_PIXEL_DEPTH 32


#define WORLD_DIMENSION_X = 1000 // kilometers
#define WORLD_DIMENSION_Y = 1000 // kilometers

//#define GRAVITY 10.0
// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
const cpVect gravity = cpv(0.0f, 0.10f);

const double PI = 3.14159265359;
const float timeStep = 1.0f/60.0f;

//const enum image_list { IMG_NONE, IMG_SPACE_BG, IMG_BALL, IMG_SPACESHIP };

static bool DO_DEBUG = 1;



#endif // !CONFIG_H

