/*
	Space Ripoff - 2D Space Game
	By: Lansdon Page, Steven Ahl
	Started: 12/15/2012


*/


// SFML + Chipmunk
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <chipmunk/chipmunk.h>

// STL
#include <iostream>
#include <sstream>

// Space Ripoff
#include "config.h"
#include "debug.h"
#include "GameObject.h"
#include "goShip.h"
#include "GameObjectManager.h"




int main(int argc, int argv[]) {
	std::cout << "SPACE RIPOFF GAME OF EPIC PROPORTIONS!!\n";

	Settings *settings = new Settings();		// ABSOLUTELY CRITICAL TO INITIALIZE THIS STRUCT - IT IS PROPOGATED EVERYWHERE!
	settings->InitializeGame(cpSpaceNew(),
							new sf::RenderWindow(sf::VideoMode(START_RESOLUTION_X, START_RESOLUTION_Y, START_PIXEL_DEPTH), TITLE),
							new Images(),
							new sf::Clock()
							);
	GameObjectManager* goManager = GameObjectManager::getInstance(settings);// = GameObjectManager::getInstance();

	// SFML Setup ********************************************
//    sf::RenderWindow App(sf::VideoMode(START_RESOLUTION_X, START_RESOLUTION_Y, START_PIXEL_DEPTH), TITLE);
	settings->app->UseVerticalSync(false);
//	sf::Clock Clock;		// Master game clock -- running time
	float accumulator = 0; 	// tracks physics engine timestep
    float Framerate = 0; 
	sf::String debugMove("");
	debugMove.SetPosition(700, 550);
	// ******************************************************


	/****************************************************************************
		Chipmunk Init
	****************************************************************************/
	cpFloat time = 0; 
 
	// Create an empty space.
	cpSpace *space = settings->space;		// redundant reference for main.
	cpSpaceSetGravity(settings->space, gravity);
  
	// Screen Borders - Add static line segment shapes
	//sf::Shape borderBottom = sf::Shape::Line(0, 600, 800, 600, 2, sf::Color::Red);
	sf::Shape borderTop = sf::Shape::Line(0, 0, 800, 0, 2, sf::Color::Red);
	sf::Shape borderLeft = sf::Shape::Line(0, 0, 0, 600, 2, sf::Color::Red);
	//sf::Shape borderRight = sf::Shape::Line(800, 0, 800, 600, 2, sf::Color::Red);
	sf::Shape borderBottom = sf::Shape::Line(0, 300, 800, 300, 2, sf::Color::Red);
//	sf::Shape borderTop = sf::Shape::Line(0, 0, 400, 0, 2, sf::Color::Red);
//	sf::Shape borderLeft = sf::Shape::Line(0, 0, 0, 300, 2, sf::Color::Red);
	sf::Shape borderRight = sf::Shape::Line(400, 0, 400, 600, 2, sf::Color::Red);

	cpShape *cps_brdrBot = cpSegmentShapeNew(space->staticBody, cpv(0, 600), cpv(800, 600), 0);
	cpShape *cps_brdrTop = cpSegmentShapeNew(space->staticBody, cpv(0, 0), cpv(800, 0), 0);					// Todo - Move this to object manager
	cpShape *cps_brdrL = cpSegmentShapeNew(space->staticBody, cpv(0, 0), cpv(0, 600), 0);
	cpShape *cps_brdrR = cpSegmentShapeNew(space->staticBody, cpv(800, 0), cpv(800, 600), 0);

//	cpShapeSetFriction(ground, 1);
	cpSpaceAddShape(space, cps_brdrBot);
	cpSpaceAddShape(space, cps_brdrTop);
	cpSpaceAddShape(space, cps_brdrL);
	cpSpaceAddShape(space, cps_brdrR);
     
	// GAME OBJECT TEST
//	GameObject goBall(settings);
//	goShip goShip(settings); //, settings->images.getImageById(image_list::IMG_SPACESHIP));
//	goShip* testShip = static_cast<goShip*>(goManager->createObject(settings->OBJ_SHIP));
	GameObject* goTemp = goManager->createObject(settings->OBJ_SHIP);
	goShip* testShip = static_cast<goShip*>(goTemp);
//	goBullet testBullet(settings);
//	GameObject* goTemp2 = goManager->createBullet(settings->OBJ_BULLET, goTemp);
//	goBullet* testShip2 = static_cast<goBullet*>(goTemp2);
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
	debugTxt1.SetSize(18.f);
    debugTxt1.Move(10.f, 450.f);
//    debugTxt1.SetColor(sf::Color(100, 100, 100));

	// Ship debug
	sf::String debugTxtShip;
	debugTxtShip.SetSize(18.f);
    debugTxtShip.Move(10.f, 10.f);


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

    while (settings->app->IsOpened()) {
		shipThrusterActivated = false;
		Framerate = 1.f / settings->app->GetFrameTime();
		accumulator += settings->app->GetFrameTime();

		// FPS Display (refresh every 60 frames)
		if(++fpsCount >= 60) {
			ssFps.str("");
			ssFps << "FPS=" << (fpsSum / fpsCount);   // display average framerate per 60 frames
			fpsTxt.SetText(ssFps.str());
			fpsSum = fpsCount = 0;			// reset
		} else { fpsSum += Framerate; }

        // Handle events
        sf::Event Event;
        while (settings->app->GetEvent(Event)) {
			debugMove.SetText("");
            // Window closed or escape key pressed : exit
            if ((Event.Type == sf::Event::Closed) || 
               ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))) {
				settings->app->Close();
                break;
            }
			if(Event.Type == sf::Event::KeyPressed) {
				if(Event.Key.Code == sf::Key::Right) {
					testShip->pulseRotateCW();
					debugMove.SetText("RIGHT");
				}
				else if(Event.Key.Code == sf::Key::Left) {
					testShip->pulseRotateCCW();
					debugMove.SetText("LEFT");
				}
				else if(Event.Key.Code == sf::Key::Up) {
					testShip->pulseThrustForward();
					shipThrusterActivated = true;
					debugMove.SetText("UP");
				}
				else if(Event.Key.Code == sf::Key::Down) {
					testShip->pulseThrustBack();
					shipThrusterActivated = true;
					debugMove.SetText("DOWN");
				}
				else if(Event.Key.Code == sf::Key::S) {
					testShip->setThrusterActive(shipThrusterActivated = false);
					debugMove.SetText("S");
				}
				else if(Event.Key.Code == sf::Key::F11) {
					GameObjectManager::getInstance(settings)->createBullet(settings->OBJ_BULLET, goTemp);
				}
				else if(Event.Key.Code == sf::Key::F12) {
					DO_DEBUG = !DO_DEBUG;
				}
				else if(Event.Key.Code == sf::Key::Space) {
					testShip->fireBullet();
				}
			}
        }

        if (IsPlaying) {
			// Toggle Active Ship Thrusters
//			testShip->setThrusterActive(shipThrusterActivated);

			// Update physics
			while( accumulator >= timeStep ) {
//				++timeStepCount;
				cpSpaceStep(space, timeStep);
				accumulator -= timeStep;
			}

			goManager->updateObjects();

//			//printf(
//			//	"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
//			//	time, pos.x, pos.y, vel.x, vel.y
//			//);
			if(DO_DEBUG) {
				ssDebug.str("");
				ssDebug <<	"Super sweet Space Ripoff\n" <<
//					"Time: " << (int)(settings->masterClock.GetElapsedTime()) << "\n" <<
							"Pos=(" << (int)(testShip->getPos().x) << "," << (int)(testShip->getPos().y) << ")\n" <<
							"Center=(" << (int)(testShip->getSprite()->GetCenter().x) << "," << (int)(testShip->getSprite()->GetCenter().y) << ")\n" <<
							"velocity=("<< (int)(testShip->getVel().x) << "," << (int)(testShip->getVel().y) << ")\n" <<
							"thrust=("<< (int)(testShip->getThrusterMag()) << ")\n" <<
							"Force=(" << (int)testShip->getForce().x << "," << (int)testShip->getForce().y << ")\n" <<
							"ObjManagerTotal=("<< goManager->getObjTotal() << ")\n";
				debugTxt1.SetText(ssDebug.str());
				// SHIP DEBUG
				ssDebug.str("");
				ssDebug <<	"Pos=(" << (int)(testShip->getPos().x) << "," << (int)(testShip->getPos().y) << ")\n" <<
							"Center=(" << (int)(testShip->getSprite()->GetCenter().x) << "," << (int)(testShip->getSprite()->GetCenter().y) << ")\n" <<
							"sprite - width="<< (int)(testShip->getSprite()->GetSize().x) << " height=" << (int)(testShip->getSprite()->GetSize().y) << ")\n" <<
							"shape - l="<< (int)(testShip->getFirstShape()->bb.l) << ")\n" <<
							"shape - r="<< (int)(testShip->getFirstShape()->bb.r) << ")\n" <<
							"shape - b="<< (int)(testShip->getFirstShape()->bb.b) << ")\n" <<
							"shape - t="<< (int)(testShip->getFirstShape()->bb.t) << ")\n";
				debugTxtShip.SetText(ssDebug.str());
			}

 
		}

//		// DRAW *******************************************************************
//        // Clear the window
        settings->app->Clear();

		goManager->drawObjects();
		
		if(DO_DEBUG) settings->app->Draw(debugTxt1);
		
		settings->app->Draw(borderBottom);
		settings->app->Draw(borderTop);
		settings->app->Draw(borderLeft);
		settings->app->Draw(borderRight);


		// TEXT
		settings->app->Draw(debugTxtShip);
		settings->app->Draw(controlsTxt);
		settings->app->Draw(fpsTxt);
		settings->app->Draw(debugMove);

//        // Display things on screen
        settings->app->Display();
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