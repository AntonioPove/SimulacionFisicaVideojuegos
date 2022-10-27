#pragma once
#include "Particle.h"
#include <string>
#include <list>
#include <random>

class ParticleSystem;

class ParticleGenerator
{
	friend class Firework;
public:
	std::string _name;

	ParticleGenerator(std::string name, Particle* p, int n, 
		Vector3 pos, Vector3 vel, ParticleSystem* s);
	~ParticleGenerator();

	void setParticle(Particle* model) { this->_model = model;};

	virtual std::list<Particle*> generateParticles(double t) = 0;

protected:

	Vector3 _meanPos;
	Vector3 _meanVel;

	double _genProbably;
	int _num_particles;
	Particle* _model;

	ParticleSystem* pSys;

	double _timeGen;
	double _lastGen;
	double _currentTime;
};

