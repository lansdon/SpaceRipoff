#pragma once

// STL
#include <set>

// Space Junk
#include "Settings.h"
#include "GameObject.h"
#include "goBullet.h"
#include "goShip.h"



class GameObjectManager
{
public:
    static GameObjectManager* getInstance(Settings* _settings);
	typedef std::set<GameObject*> object_container_t;
    GameObject* createObject(Settings::object_type type);
    GameObject* createBullet(Settings::object_type type, GameObject* shooter);
	GameObject* createBullet(goConfig& new_config);
    object_container_t::iterator destroyObject(GameObject* obj);
    void updateObjects();
	void drawObjects();
	unsigned int getObjTotal() { return objList.size(); };



private:
    GameObjectManager();
    GameObjectManager(const GameObjectManager& copy);           // not implemented
    GameObjectManager& operator=(const GameObjectManager& copy); // Not Implemented
    ~GameObjectManager();

	Settings* settings;


    object_container_t objList;
	void destroyObject(object_container_t::iterator& it);				// Overloaded destroy object used during iterating over list 
};

