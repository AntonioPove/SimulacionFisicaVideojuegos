#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"

class Proyectil : public Particle
{
public:
	Proyectil(Vector3 pos_, int vel_, double size_, double mass_, double deathTime, Vector3 rgb);
	~Proyectil();

	bool integrate(double t) override;

	Proyectil* clone();

protected:

	Vector3 a = { 0, -2, 0 };
	double d = 0.999;

	double dTime;
	bool fIteration = false;

	double mass;
	double v;
	Vector3 vel;
	Vector3 p;

	Vector3 vel0 = { 0,0,0 };
};

