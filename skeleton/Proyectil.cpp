#include "Proyectil.h"

Proyectil::Proyectil(Vector3 pos_, int vel_, double size_, double mass_, double deathTime, Vector3 rgb) :
	Particle(pos_, vel0, size_, a, d, dTime, rgb)
{
	v = vel_;
	mass = mass_;
	dTime = deathTime;
	p = GetCamera()->getDir();
	vel = vel_ * p;
}

Proyectil::~Proyectil()
{
}

bool Proyectil::integrate(double t)
{

	if (!fIteration)
	{
		iniTime = t;
		fIteration = !fIteration;
	}
	pos.p += vel * t;
	vel = (vel * pow(d, t)) + ((a*mass)* t) ;

	if (iniTime + dTime < t) 
		return false;

	return true;
}

Proyectil* Proyectil::clone()
{
	Proyectil* p;
	p = new Proyectil(this->p, this->v, this->size, this->mass, this->dTime, this->rgb);
	return p;
}
