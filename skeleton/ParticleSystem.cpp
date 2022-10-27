#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{

	fountainParticle = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.8, { 0, -2, 0 }, 10, 1, { 1, 0, 1 });
	fountainParticle1 = new Particle({ 0 ,0, 0 }, { 0, 100, 0 }, 0.8, { 0, -2, 0 }, 10, 5, { 0, 1, 1 });

	fireworkP = new Particle({ 0,0,0 }, { 10, 10, 10 }, 0.5, { 0, 0, 0 }, 5, 1, { 0, 1,0.5 });

	devTip_pos_Gau = { 1, 0, 1 };
	devTip_vel_Gau = { 3, 0, 3 };

}

ParticleSystem::~ParticleSystem()
{
	for (Particle* p : _particles)
	{
		delete p;
		p = nullptr;
	}
	_particles.clear();

	for (ParticleGenerator* g : _particles_generator)
	{
		delete g;
		g = nullptr;
	}
	_particles_generator.clear();
}

void ParticleSystem::update(double t)
{
	auto i = _particles.begin();
	while (i != _particles.end()) {
		if (!(*i)->integrate(t)) {

			if (auto f = dynamic_cast<Firework*>((*i)))
			{
				std::cout << "exploto";
				auto newsP = f->explode();

				for (auto n : newsP)
					_particles.push_back(n);
			}
			
			delete (*i);
			i = _particles.erase(i);
		}
		else
			i++;
	}

	for (auto i = _particles_generator.begin(); i != _particles_generator.end(); i++)
	{
		auto newParticle = (*i)->generateParticles(t);

		while (!newParticle.empty())
		{
			_particles.push_back(newParticle.front());
			newParticle.pop_front();
		}
		newParticle.clear();
	}
}

void ParticleSystem::addParticleGenerator(GeneratorType generatorSys, Vector3 p, Vector3 v, int n)
{
	switch (generatorSys)
	{
	case ParticleSystem::Gau:
		_particles_generator.push_back(
			new GaussianParticleGenerator(this, "Gau", fountainParticle->clone(),
				n, p, v, devTip_pos_Gau, devTip_vel_Gau));
		break;
	case ParticleSystem::Uni:
		_particles_generator.push_back(
			new UniformParticleGenerator(this, "Uni", fountainParticle1->clone(), n, p, v));
		break;
	default:
		break;
	}
}

void ParticleSystem::createFireworkSystem(int n)
{
	std::shared_ptr<CircleGenerator> gen1(new CircleGenerator(this, "fireWork1",
		fireworkP, 10, { 0, 10,0 }, { 0, 0, 0 }));

	std::shared_ptr<CircleGenerator> gen2(new CircleGenerator(this, "fireWork2",
		fountainParticle1, 10, { 5,5,5 }, { 0, 0, 0 }));

	std::shared_ptr<CircleGenerator> gen3(new CircleGenerator(this, "fireWork3",
		new Firework({ 0, 0, 0 }, { 0, 0 ,0 }, 1, { 0, -2, 0 }, 0.5, 1, { 0.3, 0.2, 1 }, { gen1 })
		, 2, {10,10,10}, {0,0,0}));

	if (n == 1) {
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 50 ,0 }, 1, { 0, -2, 0 }, 0.5, 1, { 0.6,0.9,1 }, { gen1 }));
	}
	else if (n == 2)
	{
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 100 ,0 }, 1, { 0, -2, 0 }, 0.5, 0.2, { 0,1,0 }, { gen2 }));
	}
	else if (n == 3)
	{
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 50 ,0 }, 1, { 0, -2, 0 }, 0.5, 1, { 1,1,0 }, { gen3 }));
	}

}

void ParticleSystem::destroy()
{
	for (Particle* p : _particles)
	{
		delete p;
		p = nullptr;
	}
	_particles.clear();

	for (ParticleGenerator* g : _particles_generator)
	{
		delete g;
		g = nullptr;
	}
	_particles_generator.clear();
}

