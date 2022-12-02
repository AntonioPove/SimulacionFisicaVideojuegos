#pragma once

#include "Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator();

	virtual void updateForce(Particle* particle, double duration) = 0;
	virtual void updateForceDynamics(double duration) = 0;
	std::string _name;
	double t = -1e10;
};

