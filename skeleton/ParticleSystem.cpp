#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem()
{
	//Fuerzas Gravedad
	pfr = new ParticleForceRegistry();
	
	//Particulas gausiano/uniforme y firework
	fountainParticle = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.8, { 0, -2, 0 }, 0.99, 1, { 1, 0, 1 });
	fountainParticle1 = new Particle({ 0 ,0, 0 }, { 0, 100, 0 }, 0.8, { 0, -2, 0 }, 0.99, 5, { 0, 1, 1 });
	fireworkP = new Particle({ 0,0,0 }, { 30, 150000000, 30 }, 3, { 0, 2, 0 }, 0.99, 40, { 1, 1, 0.5 });


	//Desviaciones
	devTip_pos_Gau = { 1, 0, 1 };
	devTip_vel_Gau = { 3, 0, 3 };

	lSpawn = 0;
	tSpwan = 1.0f;
	currentTime = 0;


}

ParticleSystem::~ParticleSystem()
{
	destroy();
}

void ParticleSystem::update(double t)
{
	if (exp) expl->updateConst(t);

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

void ParticleSystem::testForces(int key)
{
	Particle* p;

	switch (key)
	{
	case 5:
		p = new Particle({ 0 ,30, 0 }, { 0, 0, 0 }, 10, { 0, 0, 0 }, 10, 1, { 1, 1, 1 });
		p->setMass(40);
		gfg = new GravityForceGenerator({0, -9.8, 0});
		_particles.push_back(p);
		pfr->addRegistry(gfg, p);
		break;
	case 6:
		p = new Particle({ 0 ,30, 0 }, { 20, 0, 20 }, 5, { 0, 0, 0 }, 0.99, 50, { 1, 0, 1 });
		p->setMass(40);
		dg = new DragGenerator(0.01, 0.02);
		_particles.push_back(p);
		pfr->addRegistry(dg, p);
		break;
	case 7:
		p = new Particle({ 10 , 10, 10 }, { 0, 0, 0 }, 5, { 0, 0, 0 }, 0.2, 50, { 0, 0, 1 });
		p->setMass(40);
		upg = new UniformWindGenerator(0.01, 0.02, { 0, -100, 0 }, 0, 0, 0, 40);
		_particles.push_back(p);
		pfr->addRegistry(upg, p);
		break;
	case 8:
		
		hurr = new Hurricane(5, { 0, 0, 0 }, 0, 0, 0, 30);

		for (auto part : _particles) {
			pfr->addRegistry(hurr, part);
		}
		break;
	case 9:

		for (int i = 0; i < 20; ++i) {

			std::default_random_engine rnd{ std::random_device{}() };
			std::uniform_real_distribution<float> interval(-30, 30);
			p = new Particle({ interval(rnd), interval(rnd), interval(rnd)}, { 0, 0, 0 }, 1, { 0, 0, 0 }, 0.2, 50, { 0, 0, 1 }, 1);
	
			_particles.push_back(p);
		}
		break;
	case 0:
		expl = new Explosion(100.0, 200, 10, 10, 10);
		exp = true;

		for (auto part : _particles) {
			pfr->addRegistry(expl, part);
		}
		break;
	default:
		break;
	}

}

void ParticleSystem::generateSpringDemo()
{
	Particle* p1 = new Particle({ 0 ,10, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 1, 0, 0 });
	Particle* p2 = new Particle({ 0 ,10, 0 }, { 0, 0, 0 },2, { 0, 0, 0 }, 0.99, 100, { 0.6, 0, 1 }, 1);
	p2->setMass(2.0);
	//p1->changeSemiImplicit();

	GravityForceGenerator* g = new GravityForceGenerator({ 0, -2, 0 });

	spring1 = new SpringForceGenerator(1000, 10, p2);
	
	pfr->addRegistry(spring1, p1);
	pfr->addRegistry(g, p1);

	_particles.push_back(p1);
	_particles.push_back(p2);


}

void ParticleSystem::generateSpringDemo2()
{
	Particle* p1 = new Particle({ -20 ,10, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.85, 100, { 1, 0, 1 });
	Particle* p2 = new Particle({ 20 ,10, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.85, 100, { 0.6, 0, 1 }, 1);
	p2->setMass(2.0);
	p1->setMass(2.0);

	SpringForceGenerator* s1 = new SpringForceGenerator(500, 10, p2);
	pfr->addRegistry(s1, p1);

	SpringForceGenerator* s2 = new SpringForceGenerator(500, 10, p1);
	pfr->addRegistry(s2, p2);

	_particles.push_back(p1);
	_particles.push_back(p2);
}

void ParticleSystem::slinky()
{

	GravityForceGenerator* g = new GravityForceGenerator({ 0, -2, 0 });

	
	Particle* p = new Particle({ 0 , 65, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 1, 0, 1 }, 1);
	Particle* p1 = new Particle({ 0 , 60, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.8, 100, { 0.6, 0, 1 });
	_particles.push_back(p1);
	Particle* p2 = new Particle({ 0 , 55, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.8, 100, { 0.6, 0, 1 });
	_particles.push_back(p2);
	Particle* p3 = new Particle({ 0 , 50, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.8, 100, { 1, 0, 1 });
	_particles.push_back(p3);
	Particle* p4 = new Particle({ 0 , 45, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.8, 100, { 0.6, 0, 1 });
	_particles.push_back(p4);
	Particle* p5 = new Particle({ 0 , 40, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.8, 100, { 1, 0, 1 });
	_particles.push_back(p5);

	pfr->addRegistry(g, p1);
	pfr->addRegistry(g, p2);
	pfr->addRegistry(g, p3);
	pfr->addRegistry(g, p4);
	pfr->addRegistry(g, p5);


	pfr->addRegistry(new SpringForceGenerator(50, 10, p), p1);

	pfr->addRegistry(new SpringForceGenerator(45, 10, p1), p);
	pfr->addRegistry(new SpringForceGenerator(40, 10, p1), p2);

	pfr->addRegistry(new SpringForceGenerator(35, 10, p2), p1);
	pfr->addRegistry(new SpringForceGenerator(30, 10, p2), p3);

	pfr->addRegistry(new SpringForceGenerator(25, 10, p3), p2);
	pfr->addRegistry(new SpringForceGenerator(20, 10, p3), p4);

	pfr->addRegistry(new SpringForceGenerator(15, 10, p4), p3);
	pfr->addRegistry(new SpringForceGenerator(10, 10, p4), p5);

	pfr->addRegistry(new SpringForceGenerator(10, 10, p5), p4);
	
}

void ParticleSystem::BuoynacyTest()
{
	Particle* p = new Particle({ 0 , 0, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 1, 0, 1 }, 1);
	_particles.push_back(p);
	p->setVolumen(8);

	buoyancy = new BuoyancyForceGenerator(1, 10, 10);
	pfr->addRegistry(buoyancy, p);

	GravityForceGenerator* g = new GravityForceGenerator({ 0, -9.8, 0 });
	pfr->addRegistry(g, p);



}

void ParticleSystem::generaFuegos(double t)
{
	std::shared_ptr<CircleGenerator> gen1(new CircleGenerator(this, "fireWork1",
		fireworkP, 10, { 0, 10,0 }, { 0, 0, 0 }));


	currentTime += t;

	if (lSpawn + tSpwan <= currentTime)
	{
		lSpawn = currentTime;

		_particles.push_back(new Firework({ 0,0,0 }, { 0, 200 ,0 }, 5,
			{ 0, -2, 0 }, 0.5, 1, { 0.6,0.9,1 }, { gen1 }));

	}

}

void ParticleSystem::generaFoso()
{
	Particle* p = new Particle({ -400 , 0, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 0, 1, 0 }, 2, {50, 20, 20});
	_particles.push_back(p);
	p->setVolumen(50 * 20 * 20);
	Particle* p1 = new Particle({ 0 , 0, 400 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 0, 1, 0.2 }, 2, { 60, 20, 20 });
	_particles.push_back(p1);
	p1->setVolumen(60  * 20 * 20);
	Particle* p2 = new Particle({ 300 , 0, 40 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 0, 1, 0 }, 2, { 30, 20, 60 });
	_particles.push_back(p2);
	p2->setVolumen(30 * 20 * 60);


	buoyancy = new BuoyancyForceGenerator(2, 10, 1000);
	pfr->addRegistry(buoyancy, p);
	pfr->addRegistry(buoyancy, p1);
	pfr->addRegistry(buoyancy, p2);

	GravityForceGenerator* g = new GravityForceGenerator({ 0, -9.8, 0 });
	pfr->addRegistry(g, p);
	pfr->addRegistry(g, p1);
	pfr->addRegistry(g, p2);

}

