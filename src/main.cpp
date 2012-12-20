/*
	Space Ripoff - 2D Space Game
	By: Lansdon Page, Steven Ahl
	Started: 12/15/2012


*/


// SFML + Chipmunk
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chipmunk/chipmunk.h>

// STL
#include <iostream>
#include <sstream>

// Space Ripoff
#include "config.h"
#include "debug.h"
#include "GameObject.h"
#include "goShip.h"




int main(int argc, int argv[]) {
	std::cout << "SPACE RIPOFF GAME OF EPIC PROPORTIONS!!\n";

	// SFML Setup ********************************************
    sf::RenderWindow App(sf::VideoMode(START_RESOLUTION_X, START_RESOLUTION_Y, START_PIXEL_DEPTH), TITLE);
	App.UseVerticalSync(false);
	sf::Clock Clock;		// Master game clock -- running time
	float accumulator = 0; 	// tracks physics engine timestep
    float Framerate = 0; 
	sf::String debugMove("");
	debugMove.SetPosition(700, 550);
	// ******************************************************
	Images images;


	/****************************************************************************
		Chipmunk Init
	****************************************************************************/
	cpFloat time = 0; 
 
	// Create an empty space.
	cpSpace *space = cpSpaceNew();
	cpSpaceSetGravity(space, gravity);
  
	// Screen Borders - Add static line segment shapes
	sf::Shape borderBottom = sf::Shape::Line(0, 600, 800, 600, 2, sf::Color::Red);
	sf::Shape borderTop = sf::Shape::Line(0, 0, 800, 0, 2, sf::Color::Red);
	sf::Shape borderLeft = sf::Shape::Line(0, 0, 0, 600, 2, sf::Color::Red);
	sf::Shape borderRight = sf::Shape::Line(800, 0, 800, 600, 2, sf::Color::Red);

	cpShape *cps_brdrBot = cpSegmentShapeNew(space->staticBody, cpv(0, 600), cpv(800, 600), 0);
	cpShape *cps_brdrTop = cpSegmentShapeNew(space->staticBody, cpv(0, 0), cpv(800, 0), 0);
	cpShape *cps_brdrL = cpSegmentShapeNew(space->staticBody, cpv(0, 0), cpv(0, 600), 0);
	cpShape *cps_brdrR = cpSegmentShapeNew(space->staticBody, cpv(800, 0), cpv(800, 600), 0);

//	cpShapeSetFriction(ground, 1);
	cpSpaceAddShape(space, cps_brdrBot);
	cpSpaceAddShape(space, cps_brdrTop);
	cpSpaceAddShape(space, cps_brdrL);
	cpSpaceAddShape(space, cps_brdrR);
     
	// GAME OBJECT TEST
	GameObject goBall(space, images.getImageById(image_list::IMG_BALL));
	goShip goShip(space, images.getImageById(image_list::IMG_SPACESHIP));

 /****************************************************************************
	END CHIPMUNK
  ****************************************************************************/



    // Load the images used in the game
    sf::Image BackgroundImage;
    if (!BackgroundImage.LoadFromFile("datas/space_bg.jpg")) {
        return EXIT_FAILURE;
    }

    // Load the text font
    sf::Font Cheeseburger;
    if (!Cheeseburger.LoadFromFile("datas/post-fx/cheeseburger.ttf"))
        return EXIT_FAILURE;

	// Initialize text ///////////////////////////////////////
	std::stringstream ssDebug;

	//Debug Text
	sf::String debugTxt1;
//    debugTxt1.SetFont(Cheeseburger);
	debugTxt1.SetSize(18.f);
    debugTxt1.Move(10.f, 450.f);
//    debugTxt1.SetColor(sf::Color(100, 100, 100));

	// Control Display
	sf::String controlsTxt;					
//    controlsTxt.SetColor(sf::Color(100, 100, 100));
	controlsTxt.SetSize(12.f);
    controlsTxt.Move(625.f, 5.f);
	controlsTxt.SetText("Controls\n"
						"UP/DOWN Arrows - thrusters\n"
						"LEFT/RIGHT Arrows - rotate\n"
						"S - Stop thrusters\n"
						"F12 - Toggle debug");

	// FPS
	std::stringstream ssFps;
	unsigned int fpsCount = 0;
	unsigned int fpsSum = 0;
	sf::String fpsTxt;
//	fpsTxt.SetColor(sf::Color(100, 100, 100));
	fpsTxt.SetSize(12.f);
    fpsTxt.Move(375.f, 575.f);

	// Create the sprites of the background
    sf::Sprite Background(BackgroundImage);

	bool shipThrusterActivated = false;
	bool IsPlaying = true;

    while (App.IsOpened()) {
		shipThrusterActivated = false;
		Framerate = 1.f / App.GetFrameTime();
		accumulator += App.GetFrameTime();

		// FPS Display (refresh every sec)
		if(++fpsCount >= 60) {
			ssFps.str("");
			ssFps << "FPS=" << (fpsSum / fpsCount);   // display average framerate per 60 frames
			fpsTxt.SetText(ssFps.str());
			fpsSum = fpsCount = 0;			// reset
		} else { fpsSum += Framerate; }

        // Handle events
        sf::Event Event;
        while (App.GetEvent(Event)) {
			debugMove.SetText("");
            // Window closed or escape key pressed : exit
            if ((Event.Type == sf::Event::Closed) || 
               ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))) {
				App.Close();
                break;
            }
			if(Event.Type == sf::Event::KeyPressed) {
				if(Event.Key.Code == sf::Key::Right) {
					goShip.pulseRotateCW();
					debugMove.SetText("RIGHT");
				}
				else if(Event.Key.Code == sf::Key::Left) {
					goShip.pulseRotateCCW();
					debugMove.SetText("LEFT");
				}
				else if(Event.Key.Code == sf::Key::Up) {
					goShip.pulseThrustForward();
					shipThrusterActivated = true;
					debugMove.SetText("UP");
				}
				else if(Event.Key.Code == sf::Key::Down) {
					goShip.pulseThrustBack();
					shipThrusterActivated = true;
					debugMove.SetText("DOWN");
				}
				else if(Event.Key.Code == sf::Key::S) {
					goShip.setThrusterActive(shipThrusterActivated = false);
					debugMove.SetText("S");
				}
				else if(Event.Key.Code == sf::Key::F12) {
					DO_DEBUG = !DO_DEBUG;
				}
			}
        }

        if (IsPlaying) {
				// Toggle Active Ship Thrusters
//			goShip.setThrusterActive(shipThrusterActivated);

			goShip.update();
//			goBall.update();
//			pos = goShip.getPos();
//			vel = goShip.getVel();
//
//			//printf(
//			//	"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
//			//	time, pos.x, pos.y, vel.x, vel.y
//			//);
			if(DO_DEBUG) {
				ssDebug.str("");
				ssDebug <<	"Super sweet Space Ripoff\n" <<
							"Time: " << (int)Clock.GetElapsedTime() << "\n" <<
							"Pos=(" << (int)(goShip.getPos().x) << "," << (int)(goShip.getPos().y) << ")\n" <<
							"velocity=("<< (int)(goShip.getVel().x) << "," << (int)(goShip.getVel().y) << ")\n" <<
							"thrust=("<< (int)(goShip.getThrusterMag()) << ")\n" <<
							"Force=(" << (int)goShip.getForce().x << "," << (int)goShip.getForce().y << ")\n";
				debugTxt1.SetText(ssDebug.str());
			}

			// Update physics
			while( accumulator >= timeStep ) {
//				++timeStepCount;
				cpSpaceStep(space, timeStep);
				accumulator -= timeStep;
			}
 
		}

//		// DRAW *******************************************************************
//        // Clear the window
        App.Clear();
//
//        // Draw the background, paddles and ball sprites
//        App.Draw(Background);
//		if(goShip.getSprite())
			App.Draw(*goShip.getSprite());
//		if(goBall.getSprite())
//			App.Draw(*goBall.getSprite());
////		App.Draw(*goBall.getShape());
		
		if(DO_DEBUG) App.Draw(debugTxt1);
		
		App.Draw(controlsTxt);
		App.Draw(fpsTxt);
//		App.Draw(borderBottom);
//		App.Draw(borderTop);
//		App.Draw(borderLeft);
//		App.Draw(borderRight);
		App.Draw(debugMove);
//
//
//        // If the game is over, display the end message
//        if (!IsPlaying)
//            App.Draw(debugTxt1);
//
//        // Display things on screen
        App.Display();
//		// END DRAW ****************************************************************


    }


	// Clean up our objects and exit!
	cpShapeFree(cps_brdrTop);
	cpShapeFree(cps_brdrBot);
	cpShapeFree(cps_brdrL);
	cpShapeFree(cps_brdrR);
	cpSpaceFree(space);


    return EXIT_SUCCESS;
}






void chipmunkConfig() {


}