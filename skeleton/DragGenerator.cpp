#include "DragGenerator.h"

DragGenerator::DragGenerator() : ForceGenerator()
{

}

DragGenerator::DragGenerator(const float k1, const float k2) : ForceGenerator()
{
	_k1 = k1;
	_k2 = k2;

	_wind = { 3, 0 , 0 };
}

void DragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10)) return;

	Vector3 v = particle->vel;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
	particle->addForce(dragF);

}

void DragGenerator::updateForceDynamics(physx::PxRigidDynamic* rigid, double t)
{

	if (!active)
		return;
	Vector3 v = _wind;
	//Vector3 v = rigid->getLinearVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	std::cout << dragF.x << " ";
	std::cout << dragF.y << " ";
	std::cout << dragF.z;
	std::cout << std::endl;

	rigid->addForce(dragF);

}
