#pragma once
#include "UniformWindGenerator.h"
class Hurricane : public UniformWindGenerator
{
public:

	Hurricane(float k, Vector3 air, int ax, int ay, int az, int range);
	~Hurricane() = default;

	void updateForce(Particle* particle, double t) override;


protected:

	float k_;
	int ax_, ay_, az_;
};

