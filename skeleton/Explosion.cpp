#include "Explosion.h"
#include <iostream>

Explosion::Explosion(int R, int k, int ax, int ay, int az) :ForceGenerator()
{
	R_ = R;
	k_ = k;
	
	ax_ = ax;
	ay_ = ay;
	az_ = az;

	w_ = 0;
}

void Explosion::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10)) return;

	auto p = particle->pos.p;
	Vector3 f;

	
	r_ = sqrt(pow((p.x - ax_), 2) + pow((p.y - ay_), 2) + pow((p.z - az_), 2));

	if (r_ < R_)
	{
		double mult = k_ / pow(r_, 2);
		double elev = -(t / w_);
		double mult2 = pow(e_, elev);

		f = Vector3(p.x - ax_, p.y - ay_, p.z - az_) * mult * mult2;

	}
	else
	{
		f = { 0, 0, 0 };
	}

	Vector3 v = particle->vel - f;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (k_ * drag_coef) + k_ * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	particle->addForce(dragF);
}

void Explosion::updateForceDynamics(physx::PxRigidDynamic* rigid, double t)
{

	if (!active)
		return;

	const double euler = std::exp(1.0);
	auto pos = rigid->getGlobalPose().p;
	auto difX = pos.x -ax_;
	auto difY = pos.y - ay_;
	auto difZ = pos.z - az_;

	auto r2 = pow(difX, 2) + pow(difY, 2) + pow(difZ, 2);

	if (r2 > pow(R_, 2))
	{
		return;
	}

	auto x = (k_ / r2) * difX * pow(euler, (-t / w_));
	auto y = (k_ / r2) * difY * pow(euler, (-t / w_));
	auto z = (k_ / r2) * difZ * pow(euler, (-t / w_));

	Vector3 force(x, y, z);


	rigid->addForce(force);
}
