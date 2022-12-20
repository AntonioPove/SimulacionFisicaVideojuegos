#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include "DynamicsForceRegistry.h"

#include "UniformRigidGenerator.h"
#include "GaussianRigidGenerator.h"

#include "Explosion.h"

using namespace physx;

class Player;

class WorldManager
{
public:
	WorldManager(PxPhysics* gPhysics, PxScene* gScene);
	~WorldManager();


	void addDynamicObject();
	void addStaticObject();
	void update(double t);

	//void changeAct() { exPrueba->activate(); };
	void addForce(std::list<PxRigidDynamic*> objectsD, bool insert);

	PxRigidDynamic* createPlayer(Player* p);

	void createUniform();
	void createGaussian();
	void activeDrag(float t);

	void createMap();
	void createBombs();


protected:

	bool uni = false;
	bool gau = false;

	std::list<PxRigidDynamic*> _objects;

	std::list<PxRigidDynamic*> _bombs;

	std::list<RenderItem*> _renderItems;
	RenderItem* item;
	PxPhysics* gPhysics;
	PxScene* gScene;

	PxRigidDynamic* object;

	Vector3 vel = { 0, 10, -10 };
	Vector3 size = { 3, 3, 3 };


	DynamicsForceRegistry* dfr;
	Explosion* exPrueba;
	//DragGenerator* dragPrueba;
	//UniformWindGenerator* wind_;

	UniformRigidGenerator* uniform;
	GaussianRigidGenerator* gaussian;

	double currentTime;
	double tSpwan;
	double lSpawn;

	bool drag = false;

	Player* player_;
};

