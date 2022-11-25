#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d) : ForceGenerator()
{

	_height = h;
	_volume = V;
	_liquid_density = d;

	_liquid_particle = new Particle({ 0 , 0, 0 }, { 0, 0, 0 }, 2, { 0, 0, 0 }, 0.99, 100, { 0, 0, 1 }, 2);
}

 void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	 float h = particle->pos.p.y;
	 float h0 = _liquid_particle->pos.p.y;

	 Vector3 f(0, 0, 0);
	 float immersed = 0.0;

	 if (h - h0 > _height * 0.5) 
	 { 
		 immersed = 0.0; 
	 }
	 else if(h0 - h > _height * 0.5){
		 immersed = 1.0;
	 }
	 else
	 {
		 immersed = (h0 - h) / _height + 0.5;
	 }

	 f.y = _liquid_density * _volume * immersed * 9.8;

	 particle->addForce(f);
}
