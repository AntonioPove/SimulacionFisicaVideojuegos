#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>

class Particle
{
public:
	Particle(Vector3 pos_, Vector3 Vel_, double size_, 
		Vector3 a_, double d_);
	~Particle();

	virtual bool integrate(double t);

protected:
	physx:: PxTransform pos;
	Vector3 vel;
	RenderItem* renderItem;

	Vector3 a;
	double d;
	double size;
};

