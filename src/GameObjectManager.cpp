#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {

}

GameObjectManager::~GameObjectManager() {

}

GameObjectManager* GameObjectManager::getInstance() {
    static GameObjectManager instance;
    return &instance;
//	return NULL;
}

GameObject* GameObjectManager::createObject(Settings::object_type type) {
//    GameObject* result = new GameObject(type);
//    objList.add(result);
    return NULL;
}

void GameObjectManager::destroyObject(GameObject* obj) {
//    objList.remove(obj);
//    obj->~GameObject();
}

void GameObjectManager::UpdateObjects() {
    for (object_container_t::iterator it = objList.begin(); it != objList.end(); ++it) {
        (*it)->update();
    }
}
