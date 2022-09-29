#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_, double size_, Vector3 a_, double d_) : pos(pos_)
{
	a = a_;
	d = d_;
	size = size_;
	vel = vel_;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)),
		&pos, {1, 0.5, 0.5, 1});
}

Particle::~Particle()
{
	delete renderItem;
}

bool Particle::integrate(double t)
{
	pos.p += vel * t;
	vel = (vel * pow(d, t)) + (a * t);
	return true;
}
