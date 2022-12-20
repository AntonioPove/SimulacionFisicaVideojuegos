#pragma once
#include "ParticleGenerator.h"



class UniformParticleGenerator : public ParticleGenerator
{
public:
	UniformParticleGenerator(ParticleSystem* s, std::string name, Particle* p, int n,
		Vector3 pos, Vector3 v);

	~UniformParticleGenerator() = default;

	std::list<Particle*> generateParticles(double t) override;

protected:

	
	Vector3 _vel_width;
	Vector3 _pos_width;
};

