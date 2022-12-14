#pragma once
#include <PxPhysics.h>
#include <PxScene.h>
#include <string>
#include "RenderUtils.hpp"
#include <list>
#include <random>

class WorldManager;

using namespace physx;
using namespace std;
class GaussianRigidGenerator
{
public:

	GaussianRigidGenerator(WorldManager* wm, Vector3 pos,
		Vector3 vel, double size, PxPhysics* phy, double t1, double n, Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau, double d);
	~GaussianRigidGenerator() = default;

	list<PxRigidDynamic*> generate(double t);

protected:

	double d;
	Vector3 pos_;
	Vector3 vel_;
	double size_;

	double posR_;
	double velR_;

	int nM = 100;
	int currentN = 0;

	double std_dev_t;
	double currentTime;
	double tSpwan;
	double lSpawn;
	double nSpawn;

	WorldManager* wm_;
	PxPhysics* phy_;

	Vector3 devTip_pos_Gau_;
	Vector3 devTip_vel_Gau_;

};

