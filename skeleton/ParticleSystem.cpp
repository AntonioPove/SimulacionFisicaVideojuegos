#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{
	//Fuerzas Gravedad
	pfr = new ParticleForceRegistry();
	//p1 = new Particle({ 0 ,30, 0 }, { 0, 0, 0 }, 10, { 0, 0, 0 }, 10, 1, { 1, 1, 1 });
	//p1->setMass(40);
	//gfg = new GravityForceGenerator({0, -9.8, 0});
	//_particles.push_back(p1);
	//pfr->addRegistry(gfg, p1);

	//Fuerza viento
	/*auto p2 = new Particle({ 0 ,30, 0 }, { 20, 0, 20 }, 5, { 0, 0, 0 }, 0.99, 50, { 1, 0, 1 });
	p2->setMass(40);
	dg = new DragGenerator(0.01, 0.02);
	_particles.push_back(p2);
	pfr->addRegistry(dg, p2);*/

	//Fuerza uniforme viento
	/*auto p3 = new Particle({ 10 , 10, 10 }, { 0, 0, 0 }, 5, { 0, 0, 0 }, 0.2, 50, { 0, 0, 1 });
	p3->setMass(40);
	upg = new UniformWindGenerator(0.01, 0.02, { 0, -100, 0 }, 0, 0, 0, 40);
	_particles.push_back(p3);
	pfr->addRegistry(upg, p3);*/

	//Fuerza del huracan
	//auto p4 = new Particle({ 10 , 10, 10 }, { 0, 0, 0 }, 5, { 0, 0, 0 }, 0.2, 50, { 0, 0, 1 });
	//p4->setMass(20);
	//hurr = new Hurricane(5, { 0, 0, 0 }, 0, 0, 0, 30);
	//_particles.push_back(p4);
	//pfr->addRegistry(hurr, p4);

	//Explosion
	//auto p4 = new Particle({ 10 , 10, 10 }, { 0, 0, 0 }, 5, { 0, 0, 0 }, 0.2, 50, { 0, 0, 1 });
	//p4->setMass(20);
	//hurr = new Hurricane(5, { 0, 0, 0 }, 0, 0, 0, 30);
	//_particles.push_back(p4);
	//pfr->addRegistry(hurr, p4);


	//Particulas gausiano/uniforme y firework
	fountainParticle = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.8, { 0, -2, 0 }, 0.99, 1, { 1, 0, 1 });
	fountainParticle1 = new Particle({ 0 ,0, 0 }, { 0, 100, 0 }, 0.8, { 0, -2, 0 }, 0.99, 5, { 0, 1, 1 });
	fireworkP = new Particle({ 0,0,0 }, { 10, 10, 10 }, 0.5, { 0, 0, 0 }, 0.99, 1, { 0, 1,0.5 });
	fireworkP = new Particle({ 0,0,0 }, { 10, 10, 10 }, 0.5, { 0, 0, 0 }, 0.99, 1, { 0, 1,0.5 });


	//Desviaciones
	devTip_pos_Gau = { 1, 0, 1 };
	devTip_vel_Gau = { 3, 0, 3 };

}

ParticleSystem::~ParticleSystem()
{
	destroy();
}

void ParticleSystem::update(double t)
{
	pfr->updateForces(t);

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
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 50 ,0 }, 1, 
			{ 0, -2, 0 }, 0.5, 1, { 0.6,0.9,1 }, { gen1 }));
	}
	else if (n == 2)
	{
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 100 ,0 }, 1, 
			{ 0, -2, 0 }, 0.5, 0.2, { 0,1,0 }, { gen2 }));
	}
	else if (n == 3)
	{
		_particles.push_back(new Firework({ 0,0,0 }, { 0, 50 ,0 }, 1, 
			{ 0, -2, 0 }, 0.5, 1, { 1,1,0 }, { gen3 }));
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

