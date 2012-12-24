#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() :
	settings(NULL)
{

}

GameObjectManager::~GameObjectManager() {
    for (object_container_t::iterator it = objList.begin(); it != objList.end(); ++it) {
//		it = destroyObject(it);
		delete *it;
	}
}

GameObjectManager* GameObjectManager::getInstance(Settings* _settings) {
    static GameObjectManager instance;
	instance.settings = _settings;
    return &instance;
}

GameObject* GameObjectManager::createObject(Settings::object_type type) {
    GameObject* result = NULL;
	switch(type) {
//		case Settings::OBJ_BULLET:	result = new goBullet(settings); break;
		case Settings::OBJ_SHIP:	result = new goShip(goConfig(
			50.f,				// radius
			10.0f,				// mass
			Images::IMG_SPACESHIP,	// Image id
			cpv(400, 300),		// position
			0.f,				// angle
			cpvzero,			// velocity
			cpvzero,			// force
			settings));
		break;
	}
    objList.insert(result);
    return result;
}

GameObject* GameObjectManager::createBullet(Settings::object_type type, GameObject* shooter) {
    GameObject* result = NULL;
	switch(type) {
		case Settings::OBJ_BULLET:	result = new goBullet(goConfig(
			50.f,				// radius
			10.0f,				// mass
			Images::IMG_BALL,	// Image id
			cpv(20, 40),		// position
			0.f,				// angle
			cpvzero,			// velocity
			cpvzero,			// force
			settings,			// settings
			shooter));			// owner/shooter
		break;
	}
    objList.insert(result);
    return result;
}

GameObject* GameObjectManager::createBullet(goConfig& new_config) {
    GameObject* result = NULL;

//	switch(type) {
//		case Settings::OBJ_BULLET:	
			result = new goBullet(new_config);			// owner/shooter
//		break;
//	}
    objList.insert(result);
    return result;
}


GameObjectManager::object_container_t::iterator GameObjectManager::destroyObject(GameObject* obj) {
	object_container_t::iterator it;
	for (it = objList.begin(); it != objList.end(); ++it) {
		if(*it == obj) {
			it = destroyObject(*it);
			break;
		}
	}
	return it;
}

void GameObjectManager::destroyObject(object_container_t::iterator& it) {
	delete *it;
//    return objList.erase(it);
}

void GameObjectManager::updateObjects() {
    for (object_container_t::iterator it = objList.begin(); it != objList.end(); ++it) {
        (*it)->update();
    }
}


void GameObjectManager::drawObjects() {
    for (object_container_t::iterator it = objList.begin(); it != objList.end(); ++it) {
		(*it)->draw();
	}
}
