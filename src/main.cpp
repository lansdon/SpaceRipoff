/*
	Space Ripoff - 2D Space Game
	By: Lansdon Page, Steven Ahl
	Started: 12/15/2012


*/



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
//#include <chipmunk/chipmunk.h>
#include <iostream>
#include "config.h"



int main(int argc, int argv[]) {

	std::cout << "SPACE RIPOFF GAME OF EPIC PROPORTIONS!!\n";

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
	sf::String End;
    End.SetFont(Cheeseburger);
	End.SetSize(60.f);
    End.Move(150.f, 200.f);
    End.SetColor(sf::Color(50, 50, 250));
	End.SetText("Super sweet Space Ripoff");

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
                App.Close();
                break;
            }
        }

        if (IsPlaying) {
			// GAME LOGIC HERE

//			if (Ball.GetPosition().x + Ball.GetSize().x > App.GetView().GetRect().GetWidth())
		}


        // Clear the window
        App.Clear();

        // Draw the background, paddles and ball sprites
        App.Draw(Background);
        App.Draw(Ball);
		App.Draw(End);


        // If the game is over, display the end message
        if (!IsPlaying)
            App.Draw(End);

        // Display things on screen
        App.Display();
    }

    return EXIT_SUCCESS;

	std::cin.get();

}