#pragma once
#include "Particle.h"
#include "CircleGenerator.h"
#include <list>
#include <memory>



class Firework : public Particle
{
public:
	Firework(Vector3 pos_, Vector3 Vel_, double size_,
		Vector3 a_, double d_, double deathTime, Vector3 rgb, std::list<std::shared_ptr<CircleGenerator>> c);
	~Firework();


	bool update(double t);
	Particle* clone() const override;
	std::list<Particle*> explode();

	
private:

	std::list<ParticleGenerator*>  _particles_generator_Fireworks;

	std::list<std::shared_ptr<CircleGenerator>> c_;
	
};

