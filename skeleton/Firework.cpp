#include "Firework.h"

Firework::Firework(Vector3 pos_, Vector3 Vel_, double size_, Vector3 a_, double d_, double deathTime, Vector3 rgb
, std::list<std::shared_ptr<CircleGenerator>> c)
	: Particle(pos_, Vel_, size_, a_, d_, deathTime, rgb)
{
	c_ = c;
}

Firework::~Firework()
{}

bool Firework::update(double t)
{
	iniTime += t;

	pos.p += vel * t;
	vel = (vel * pow(d, t)) + (a * t);

	if (iniTime > dTime)
		return false;

	return true;
}

Particle* Firework::clone() const
{
	Firework* p;
	p = new Firework(this->pos.p, this->vel, this->size, this->a, this->d, this->dTime, this->rgb, this->c_);
	return p;
}

std::list<Particle*> Firework::explode()
{
	std::list<Particle*> _particle;

	for (auto g : c_)
	{
		
		g->_model->pos.p = this->pos.p;
		for (auto p : g->generateParticles(0))
		{
			_particle.push_back(p);
		}
	}

	return _particle;
}
