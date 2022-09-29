#include "Proyectil.h"

Proyectil::Proyectil(Vector3 pos_, int vel_, double size_, double mass_) :
	Particle(pos_, vel0, size_, a, d)
{
	mass = mass_;
	p = GetCamera()->getDir();
	vel = vel_ * p;
}

Proyectil::~Proyectil()
{
}

bool Proyectil::integrate(double t)
{
	pos.p += vel * t;
	vel = (vel * pow(d, t)) + ((a*mass)* t) ;
	return false;
}
