#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"

using namespace physx;

class WorldManager
{
public:
	WorldManager(PxPhysics* gPhysics, PxScene* gScene);
	~WorldManager() = default;


	void addDynamicObject();
	void addStaticObject();

protected:
	RenderItem* item;
	PxPhysics* gPhysics;
	PxScene* gScene;

	Vector3 vel = { 0, 10, -10 };
	Vector3 size = { 3, 3, 3 };

};

