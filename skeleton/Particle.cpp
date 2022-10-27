#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_, double size_, Vector3 a_, double d_
, double deathTime, Vector3 _rgb) : pos(pos_), dTime(deathTime)
{
	a = a_;
	d = d_;
	size = size_;
	vel = vel_;
	rgb = _rgb;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)),
		&pos, {rgb.x, rgb.y, rgb.z, 1});
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

bool Particle::integrate(double t)
{
	iniTime += t;

	pos.p += vel * t;
	vel = (vel * pow(d, t)) + (a * t);

	if (iniTime > dTime) 
		return false;


	return true;
}

Particle* Particle::clone() const
{
	Particle* p;
	p = new Particle(this->pos.p, this->vel, this->size,
		this->a, this->d, this->dTime, this->rgb);
	return p;
}
