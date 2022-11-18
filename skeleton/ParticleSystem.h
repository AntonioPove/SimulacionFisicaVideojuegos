#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "CircleGenerator.h"
#include "Firework.h"

#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "DragGenerator.h"
#include "UniformWindGenerator.h"
#include "Hurricane.h"
#include "Explosion.h"

#include "SpringForceGenerator.h"

#include <list>
#include <string>
#include <memory>

class ParticleSystem
{
public:

	enum GeneratorType { Gau, Uni };

	ParticleSystem();
	~ParticleSystem();

	void update(double t);

	void addParticleGenerator(GeneratorType generator, Vector3 p, Vector3 v, int n);

	void createFireworkSystem(int n);

	std::list<Particle*> getParticleVector() { return _particles; };

	void destroy();


	void testForces(int key);
	
	void generateSpringDemo();

	void generateSpringDemo2();
	
	void slinky();


protected:

	std::list<ParticleGenerator*> _particles_generator;
	std::list<Particle*> _particles;

	Particle* p1;

	Particle* fountainParticle;
	Particle* fountainParticle1;
	Particle* fireworkP;
	Particle* fireworkP1;
	Particle* fireworkP2;

	Vector3 devTip_pos_Gau;
	Vector3 devTip_vel_Gau;

	ParticleForceRegistry* pfr;
	GravityForceGenerator* gfg;
	DragGenerator* dg;
	UniformWindGenerator* upg;
	Hurricane* hurr;

	Explosion* expl;
	bool exp = false;

	//Parte 1
	SpringForceGenerator* spring1;



};

