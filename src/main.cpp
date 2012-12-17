/*
	Space Ripoff - 2D Space Game
	By: Lansdon Page, Steven Ahl
	Started: 12/15/2012


*/



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chipmunk/chipmunk.h>
#include <iostream>
#include <sstream>
#include "config.h"
#include "debug.h"




int main(int argc, int argv[]) {

	std::cout << "SPACE RIPOFF GAME OF EPIC PROPORTIONS!!\n";

	/****************************************************************************
		Chipmunk hello world
	****************************************************************************/

	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	cpVect gravity = cpv(0, 10);
  
	// Create an empty space.
	cpSpace *space = cpSpaceNew();
	cpSpaceSetGravity(space, gravity);
  
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
	sf::Shape borderBottom = sf::Shape::Line(0, 0, 800, 500, 5, sf::Color::White);
	borderBottom.Move(0, 50);
	cpShape *ground = cpSegmentShapeNew(space->staticBody, cpv(0, 50), cpv(800, 550), 0);
	cpShapeSetFriction(ground, 1);
	cpSpaceAddShape(space, ground);
  
  // Now let's make a ball that falls onto the line and rolls off.
  // First we need to make a cpBody to hold the physical properties of the object.
  // These include the mass, position, velocity, angle, etc. of the object.
  // Then we attach collision shapes to the cpBody to give it a size and shape.
  
	cpFloat radius = 10;
	cpFloat mass = 1;
  
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
	cpBodySetPos(ballBody, cpv(10, 15));
  
	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
	cpShapeSetFriction(ballShape, 0.7);
	sf::Shape ballSprite = sf::Shape::Circle(0.0, 0.0, (float)radius, sf::Color(255, 255, 255)); 
  
   

	cpFloat time = 0; 
	cpVect pos = cpBodyGetPos(ballBody);
	cpVect vel = cpBodyGetVel(ballBody);
 

  /****************************************************************************
	END CHIPMUNK
  ****************************************************************************/


    // Create the window of the application
    sf::RenderWindow App(sf::VideoMode(START_RESOLUTION_X, START_RESOLUTION_Y, START_PIXEL_DEPTH), TITLE);

    // Load the images used in the game
    sf::Image BackgroundImage, BallImage;
    if (!BackgroundImage.LoadFromFile("datas/space_bg.jpg")    ||
        !BallImage.LoadFromFile("datas/pong/ball.png")) 
	{
        return EXIT_FAILURE;
    }

    // Load the text font
    sf::Font Cheeseburger;
    if (!Cheeseburger.LoadFromFile("datas/post-fx/cheeseburger.ttf"))
        return EXIT_FAILURE;

	// Initialize the end text
	sf::String debugTxt1;
    debugTxt1.SetFont(Cheeseburger);
	debugTxt1.SetSize(18.f);
    debugTxt1.Move(10.f, 500.f);
    debugTxt1.SetColor(sf::Color(100, 100, 250));
	debugTxt1.SetText("Super sweet Space Ripoff");

	// Create the sprites of the background, the paddles and the ball
    sf::Sprite Background(BackgroundImage);
    sf::Sprite Ball(BallImage);


	bool IsPlaying = true;
    while (App.IsOpened()) {
        // Handle events
        sf::Event Event;
        while (App.GetEvent(Event)) {
            // Window closed or escape key pressed : exit
            if ((Event.Type == sf::Event::Closed) || 
               ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))) {
				// Clean up our objects and exit!
				//cpShapeFree(ballShape);
				//cpBodyFree(ballBody);
				//cpShapeFree(ground);
				//cpSpaceFree(space);
				App.Close();
                break;
            }
        }

        if (IsPlaying) {
			// GAME LOGIC HERE

			  // Chipmunk
			  // Now that it's all set up, we simulate all the objects in the space by
			  // stepping forward through time in small increments called steps.
			  // It is *highly* recommended to use a fixed size time step.
//			  for(cpFloat time = 0; time < 2; time += timeStep) {
			pos = cpBodyGetPos(ballBody);
			vel = cpBodyGetVel(ballBody);
			ballSprite.SetPosition(pos.x, pos.y);

			printf(
				"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
				time, pos.x, pos.y, vel.x, vel.y
			);
			std::stringstream ssDebug;
			ssDebug << "Super sweet Space Ripoff\n" << 
						"Time: " << (int)time << "\n" <<
						"ball=(" << (int)(pos.x) << "," << (int)(pos.y) << ")\n" <<
						"velocity=("<< (int)(pos.x) << "," << (int)(pos.y) << ")\n";
			debugTxt1.SetText(ssDebug.str());

			cpSpaceStep(space, timeStep);
			time += timeStep;
 
		}


        // Clear the window
        App.Clear();

        // Draw the background, paddles and ball sprites
        App.Draw(Background);
//        App.Draw(Ball);
		App.Draw(ballSprite);
		App.Draw(debugTxt1);
		App.Draw(borderBottom);

        // If the game is over, display the end message
        if (!IsPlaying)
            App.Draw(debugTxt1);

        // Display things on screen
        App.Display();
    }


	// Clean up our objects and exit!
	cpShapeFree(ballShape);
//	cpBodyFree(ballBody);      //Causing a crash for some reason = memory error
	cpShapeFree(ground);
	cpSpaceFree(space);


//	std::cin.get();

    return EXIT_SUCCESS;


}

void chipmunkConfig() {


}