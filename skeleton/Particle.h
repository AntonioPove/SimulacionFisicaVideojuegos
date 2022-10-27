#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>

class Particle
{
public:
	Particle(Vector3 pos_, Vector3 Vel_, double size_, 
		Vector3 a_, double d_, double deathTime, Vector3 rgb);
	~Particle();

	virtual bool integrate(double t);
	virtual Particle* clone() const;


	physx::PxTransform pos;
	Vector3 vel;

protected:
	RenderItem* renderItem;

	double iniTime = 0;
	bool fIteration = false;
	double dTime;
	Vector3 a;
	Vector3 rgb;
	double d;
	double size;
};

