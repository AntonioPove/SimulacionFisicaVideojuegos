#pragma once
#include "WorldManager.h"
#include "ForceGenerator.h"
#include "ParticleSystem.h"


class Player : public ForceGenerator
{
public:
	Player(WorldManager* wm, ParticleSystem* ps);
	~Player() = default;

	void updatePlayer(double t);
	void inputPlayer(char key);

	void moveInicial();

	virtual void updateForce(Particle* particle, double t) {};
	virtual void updateForceRigids(physx::PxRigidDynamic* particle, double t) {};

	bool collision(PxTransform bombs);
	bool final(PxTransform final);


private:

	PxRigidDynamic* player_;
	WorldManager* wm_;
	ParticleSystem* ps;

	float vel_;
	float sizePlayer;
	float sizeEnemies;

};

