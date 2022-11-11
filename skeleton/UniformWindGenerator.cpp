#include "UniformWindGenerator.h"

UniformWindGenerator::UniformWindGenerator(float k1, float k2, Vector3 air, int ax, int ay, int az, int range) : DragGenerator(k1, k2)
{
	_k1 = k1;
	_k2 = k2;
	air_ = air;

	MaxX = ax + range;
	MaxY = ay + range;
	MaxZ = az + range;
	MinX = ax;
	MinY = ay;
	MinZ = az;

}
UniformWindGenerator::~UniformWindGenerator()
{
}

void UniformWindGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10)) return;

	auto p = particle->pos.p;

	if (p.x < MinX || p.x > MaxX || p.y < MinY || p.y > MaxY || p.z < MinZ || p.z > MaxZ)
	{
		std::cout << "NO HAY AIRE " << std::endl;

		return;
	}

	Vector3 v = particle->vel + air_;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
	particle->addForce(dragF);

}
