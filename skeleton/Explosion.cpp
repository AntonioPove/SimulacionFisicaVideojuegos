#include "Explosion.h"

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
