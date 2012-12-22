#pragma once
#include <set>
#include "GameObject.h"
#include "Settings.h"

class GameObjectManager
{
public:
    static GameObjectManager* getInstance();
    GameObject* createObject(Settings::object_type type);
    void destroyObject(GameObject* obj);
    void UpdateObjects();


private:
    GameObjectManager();
    GameObjectManager(const GameObjectManager& copy);           // not implemented
    GameObjectManager& operator=(const GameObjectManager& copy); // Not Implemented
    ~GameObjectManager();
    typedef std::set<GameObject*> object_container_t;
    object_container_t objList;
};

