#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
public:

	GaussianParticleGenerator(ParticleSystem* s, std::string name, Particle* p, int n,
		Vector3 pos, Vector3 v, Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau);
	~GaussianParticleGenerator() = default;

	std::list<Particle*> generateParticles(double t) override;

protected:

	std::normal_distribution<double> _d { 0, 1 };

	Vector3 _devTip_pos;
	Vector3 _devTip_vel;

	double _std_dev_t;
};

