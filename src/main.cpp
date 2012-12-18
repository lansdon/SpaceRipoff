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
	// Create an empty space.
	cpSpace *space = cpSpaceNew();
	cpSpaceSetGravity(space, gravity);
  
	// Screen Borders - Add static line segment shapes
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
	sf::Shape borderBottom = sf::Shape::Line(0, 600, 800, 600, 2, sf::Color::Red);
	sf::Shape borderTop = sf::Shape::Line(0, 0, 800, 0, 2, sf::Color::Red);
	sf::Shape borderLeft = sf::Shape::Line(0, 0, 0, 600, 2, sf::Color::Red);
	sf::Shape borderRight = sf::Shape::Line(800, 0, 800, 600, 2, sf::Color::Red);
//	borderBottom.Move(0, 50);
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

	cpFloat time = 0; 
	cpVect pos = goBall.getPos();
	cpVect vel = goBall.getVel();
 

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

	// Initialize the end text
	sf::String debugTxt1;
    debugTxt1.SetFont(Cheeseburger);
	debugTxt1.SetSize(18.f);
    debugTxt1.Move(10.f, 500.f);
    debugTxt1.SetColor(sf::Color(100, 100, 250));
	debugTxt1.SetText("Super sweet Space Ripoff");

	// Create the sprites of the background
    sf::Sprite Background(BackgroundImage);
//    sf::Sprite Ball(BallImage);


	bool IsPlaying = true;
    while (App.IsOpened()) {
		Framerate = 1.f / App.GetFrameTime();
		accumulator += App.GetFrameTime();

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
					debugMove.SetText("RIGHT ARROW");
				}
				else if(Event.Key.Code == sf::Key::Left) {
					goShip.pulseRotateCCW();
					debugMove.SetText("LEFT ARROW");
				}
				else if(Event.Key.Code == sf::Key::Up) {
					goShip.pulseThrustForward();
					debugMove.SetText("Up ARROW");
				}
				else if(Event.Key.Code == sf::Key::Down) {
					goShip.pulseThrustBack();
					debugMove.SetText("DOWN ARROW");
				}
			}
        }

        if (IsPlaying) {
			// GAME LOGIC HERE
			goShip.update();
			goBall.update();
			pos = goShip.getPos();
			vel = goShip.getVel();

			//printf(
			//	"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
			//	time, pos.x, pos.y, vel.x, vel.y
			//);
			std::stringstream ssDebug;
			ssDebug <<	"Super sweet Space Ripoff\n" <<
				"FPS: " << (int)Framerate << "\n" <<
						"Time: " << (int)Clock.GetElapsedTime() << "\n" <<
						"ball=(" << (int)(pos.x) << "," << (int)(pos.y) << ")\n" <<
						"velocity=("<< (int)(pos.x) << "," << (int)(pos.y) << ")\n";
			debugTxt1.SetText(ssDebug.str());

			while( accumulator >= timeStep ) {
//				++timeStepCount;
				cpSpaceStep(space, timeStep);
				accumulator -= timeStep;
			}
 
		}

		// DRAW *******************************************************************
        // Clear the window
        App.Clear();

        // Draw the background, paddles and ball sprites
        App.Draw(Background);
		if(goShip.getSprite())
			App.Draw(*goShip.getSprite());
		if(goBall.getSprite())
			App.Draw(*goBall.getSprite());
//		App.Draw(*goBall.getShape());
		App.Draw(debugTxt1);
		App.Draw(borderBottom);
		App.Draw(borderTop);
		App.Draw(borderLeft);
		App.Draw(borderRight);
		App.Draw(debugMove);


        // If the game is over, display the end message
        if (!IsPlaying)
            App.Draw(debugTxt1);

        // Display things on screen
        App.Display();
		// END DRAW ****************************************************************
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