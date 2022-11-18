#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) : ForceGenerator()
{
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

void SpringForceGenerator::updateForce(Particle* particle , double t)
{
	auto oP = _other->pos.p;
	auto pP = particle->pos.p;

	Vector3 force = oP - pP;

	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	particle->addForce(force);
}
