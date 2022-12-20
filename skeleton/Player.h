#pragma once
#include "WorldManager.h"

class Player
{
public:
	Player(WorldManager* wm);
	~Player() = default;

	void updatePlayer(double t);
	void inputPlayer(char key);

	bool collision(std::list<PxRigidDynamic*> bombs);

private:

	PxRigidDynamic* player_;
	WorldManager* wm_;

	float vel_;
	float velJump_;

	float sizePlayer;
	float sizeEnemies;
};

