#include "Hurricane.h"

Hurricane::Hurricane(float k, Vector3 air, int ax, int ay, int az, int range) : 
	UniformWindGenerator(k, k, air, ax, ay, az, range)
{

	k_ = k;
	ax_ = ax;
	ay_ = ay;
	az_ = az;
}

void Hurricane::updateForce(Particle* particle, double t)
{
    auto p = particle->pos.p;

    if (fabs(particle->getInverseMass() < 1e-10)) return;

    Vector3 airDir = k_ * Vector3(
        -(p.z - az_),
        20 - (p.y - ay_),
        p.x - az_
    );

    Vector3 v = particle->vel - airDir;
    float drag_coef = v.normalize();
    Vector3 dragF;
    drag_coef = (_k1 * drag_coef) + _k1 * drag_coef * drag_coef;
    dragF = -v * drag_coef;

    particle->addForce(dragF);
}
