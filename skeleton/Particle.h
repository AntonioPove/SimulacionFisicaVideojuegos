#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <math.h>

class Particle
{
public:
	Particle(Vector3 pos_, Vector3 Vel_, double size_, 
		Vector3 a_, double d_, double deathTime, Vector3 rgb, int type = 0);
	~Particle();

	virtual bool integrate(double t);
	virtual Particle* clone() const;


	void addForce(const Vector3& f) { force += f; }
	void deleteForce();
	
	void setMass(float mass) { mass_ = mass; inverse_mass = 1 / mass_;};
	void setVolumen(float volume) { volume_ = volume; };

	physx::PxTransform pos;
	Vector3 vel;
	Vector3 force = {0, 0, 0};

	const float getMass() { return mass_; };
	const float getVolume() { return volume_; };
	const float getInverseMass() { return inverse_mass; };

	void changeSemiImplicit() { semiImplict = !semiImplict; };


protected:
	RenderItem* renderItem;

	//Tiempo de vida
	double iniTime = 0;
	bool fIteration = false;
	double dTime;

	//Volumen
	float volume_;


	//Atributos 
	Vector3 a;
	Vector3 rgb;
	double d;
	double size;
	
	float inverse_mass;
	float mass_;


	bool semiImplict = true;
};

