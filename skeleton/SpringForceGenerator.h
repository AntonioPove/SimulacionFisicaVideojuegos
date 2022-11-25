#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length/*, double min_l, double max_l,*/, Particle* other);
	
	virtual void updateForce(Particle* particle, double t);

	inline void setk(double k) { _k = k; };

	~SpringForceGenerator() = default;

protected:
	double _k;
	double _resting_length;
	Particle* _other;

};

