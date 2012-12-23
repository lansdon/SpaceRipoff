#pragma once
#include "gameobject.h"
class goBullet :
	public GameObject
{
public:
	goBullet(goConfig new_config);
	~goBullet(void);

	void setOwner(GameObject *shooter) { _owner = shooter; }



private:
	GameObject *_owner;				// Object that shot this bullet
	float _maxLinearVelocity;

};

