#pragma once
#include "DragGenerator.h"
class UniformWindGenerator : public DragGenerator
{
public:
	UniformWindGenerator(float k1, float k2, Vector3 air, int ax, int ay, int az, int range);
	~UniformWindGenerator();

	void updateForce(Particle* particle, double t) override;

protected:
	float _k1;
	float _k2;

	Vector3 air_;

	int MaxX;
	int MaxY;
	int MaxZ;
	int MinX;
	int MinY;
	int MinZ;

};

