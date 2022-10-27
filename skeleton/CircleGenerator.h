#pragma once
#include "GaussianParticleGenerator.h"

class CircleGenerator : public GaussianParticleGenerator
{
public:
	CircleGenerator(ParticleSystem* s, std::string name, Particle* p, int n,
		Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau);

	~CircleGenerator() = default;

	std::list<Particle*> generateParticles(double t) override;
};

