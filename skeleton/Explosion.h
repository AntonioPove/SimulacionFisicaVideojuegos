#pragma once
#include "ForceGenerator.h"
#include <cmath>


class Explosion : public ForceGenerator
{
public:
	Explosion(int R, int k, int ax, int ay, int az);
	~Explosion() = default;

	virtual void updateForce(Particle* particle, double t);

protected:

	const double e_ = 2.71828182846;

	double r_;
	int k_;

	double R_;

	double w_;

	int ax_, ay_, az_;
};

