#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_, double size_, Vector3 a_, double d_
, double deathTime, Vector3 _rgb, int type, Vector3 sizeRec) : pos(pos_), dTime(deathTime)
{
	a = a_;
	d = d_;

	mass_ = 20;
	inverse_mass = 1 / mass_;

	size = size_;
	vel = vel_;
	rgb = _rgb;

	if(type == 0)
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)),&pos, {rgb.x, rgb.y, rgb.z, 1});
	else if(type == 1)
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(size, size, size)), &pos, {rgb.x, rgb.y, rgb.z, 1});
	else if(type == 2)
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(sizeRec)), &pos, { rgb.x, rgb.y, rgb.z, 1 });
	
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
}

bool Particle::integrate(double t)
{

	if (inverse_mass <= 0.0f) 
		return true;

	iniTime += t;

	if(!semiImplict)
	pos.p += vel * t;


	Vector3 accTotal = a;
	accTotal += force * inverse_mass;

	vel += accTotal * t;
	vel *= powf(d, t);


	if (semiImplict)
		pos.p += vel * t;

	if (iniTime > dTime) 
		return false;

	deleteForce();

	return true;
}

Particle* Particle::clone() const
{
	Particle* p;
	p = new Particle(this->pos.p, this->vel, this->size, this->a, this->d, this->dTime, this->rgb);
	p->setMass(mass_);
	return p;
}

void Particle::deleteForce()
{
	force = { 0, 0, 0 };
}
