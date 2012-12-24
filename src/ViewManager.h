#pragma once

// SFML
#include <SFML\Graphics.hpp>

// STL
#include <vector>

// Space Junk
#include "Settings.h"


class ViewManager
{
public:
	ViewManager(void);
	~ViewManager(void);

	enum eViews { VIEW_DEFAULT, VIEW_SPACE } _currentView;
	eViews _currentView2;

	sf::Vector2f Center;
	sf::Vector2f HalfSize;
	sf::View View1;
	
	typedef std::vector<sf::View> view_list_t;
	view_list_t _viewList;

	void setCenter(float x, float y) { View1.SetCenter(x, y); };
	void setHalfSize(float x, float y) { View1.SetHalfSize(x, y); };

	sf::Vector2f  getCenter() { return View1.GetCenter(); };
	sf::Vector2f  getHalfSize() { return View1.GetHalfSize(); };

// There are also two helper functions to move or zoom (resize) the view :
	void viewMove(int x, int y) { View1.Move(x, y); } // Move the view of (x, y) units
	void setZoom(float x) { View1.Zoom(x); }   // Zoom by a factor of 1/2 (ie. unzoom to make the view twice larger)

// As you can see there's nothing complicated here, only a few functions to control the view's position and size.
// Using a view

// To use a view, you need to call the SetView function of the sf::RenderWindow class :

// Use our custom view
	void setView(eViews vType) { settings->app->SetView(_viewList[vType]); } 

//Any object drawn after the call to SetView (and before the next one) will be affected by the view.
//Once set, the render window keeps a link to the view so you can update it without calling SetView again, all your modifications will be automatically taken in account.

// Every render window has a default view, which always matches the initial size of the window. You can access this view, and even modify it if needed, with the GetDefaultView function :

//	sf::View& DefaultView = App.GetDefaultView();

//The default view is not updated when its window is resized : as a consequence, what's visible in your window will never be affected by its size (ie. you won't see more if you maximize the window), which is exactly what happens with a 3D camera.
//However, you can easily setup a view which always keeps the same dimension as the window, by catching the sf::Event::Resized event and updating the view accordingly.

//Accessing the default view is also convenient to go back to the initial view. For example, it can be useful if you want to draw a user interface on top of the game, which usually doesn't follow the camera.

//App.SetView(View);

// Draw the game...

//App.SetView(App.GetDefaultView());

// Draw the interface...
private:
	Settings* settings;

};

