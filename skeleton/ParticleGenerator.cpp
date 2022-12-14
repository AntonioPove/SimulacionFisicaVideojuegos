#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include  <iostream>


ParticleGenerator::ParticleGenerator(std::string name, Particle* p, int n,
	Vector3 pos, Vector3 vel, ParticleSystem* ps) : pSys(ps), _name(name), _num_particles(n)
{
	setParticle(p);
	_model->pos = physx::PxTransform(pos);
	_model->vel = vel;

	_lastGen = 0;
	_currentTime = 0;
}

ParticleGenerator::~ParticleGenerator()
{
}
