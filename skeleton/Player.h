#pragma once
#include "WorldManager.h"

class Player
{
public:
	Player(WorldManager* wm);
	~Player() = default;

	void updatePlayer(double t);
	void inputPlayer(char key);


private:

	PxRigidDynamic* player_;
	WorldManager* wm_;

	float vel_;
	float velJump_;
};

