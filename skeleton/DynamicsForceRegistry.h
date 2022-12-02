#pragma once

#include <map>
#include "ForceGenerator.h"
#include <PxPhysics.h>

typedef std::pair<ForceGenerator*, physx::PxRigidDynamic*> FRPair;


class DynamicsForceRegistry : public std::multimap<ForceGenerator*, physx::PxRigidDynamic*>
{
public:
	void updateForces(double duration)
	{
		for (auto it = begin(); it != end(); it++)
		{
			it->first->updateForceDynamics(duration);
		}
	}

	void addRegistry(ForceGenerator* fg, physx::PxRigidDynamic* p) { this->insert(FRPair(fg, p)); };

	void deleteParticleRegistry(physx::PxRigidDynamic* p)
	{
		for (auto it = begin(); it != end(); it++)
		{
			if (it->second == p)
			{
				erase(it);
			}
		}
	};
};

