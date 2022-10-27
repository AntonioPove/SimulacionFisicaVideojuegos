#include "CircleGenerator.h"

CircleGenerator::CircleGenerator(ParticleSystem* s, std::string name, Particle* p, int n,
	Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau) : 
	GaussianParticleGenerator(s, name, p, n, {0,0,0}, { 0,0,0 }, devTip_pos_Gau, devTip_vel_Gau)
{
}

std::list<Particle*> CircleGenerator::generateParticles(double t)
{
	_currentTime += t;
	std::list<Particle*> _particles = std::list<Particle*>();


	if (_timeGen + _lastGen <= _currentTime)
	{
		_lastGen = _currentTime;

		std::random_device r;
		std::default_random_engine gnd(r());
		for (auto i = 0; i < _num_particles; i++)
		{
	
			_particles.push_front(_model->clone());
			_particles.front()->pos.p += Vector3(_devTip_pos.x + _d(gnd), _devTip_pos.y + _d(gnd), _devTip_pos.z + _d(gnd));
			_particles.front()->vel += Vector3(_devTip_vel.x + _d(gnd), _devTip_vel.y + _d(gnd), _devTip_vel.z + _d(gnd));
			
		}

		return _particles;
	}
	return _particles;
}
