#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_, double size_) : pos(pos_)
{
	size = size_;
	vel = vel_;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)),
		&pos, {0.3, 0.5, 0.5, 1});
}

Particle::~Particle()
{
	delete renderItem;
}

bool Particle::integrate(double t)
{
	pos.p += vel * t;
	return true;
}
