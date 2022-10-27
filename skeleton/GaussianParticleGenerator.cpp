#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(ParticleSystem* s, std::string name, 
	Particle* particle,
	int n, Vector3 pos, Vector3 v, Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau) :
	ParticleGenerator(name, particle, n, pos, v, s),
	_devTip_pos(devTip_vel_Gau), _devTip_vel(devTip_pos_Gau)
{
}

std::list<Particle*> GaussianParticleGenerator::generateParticles(double t)
{
	_currentTime += t;
	std::list<Particle*> _particles = std::list<Particle*>();

	//Se crea o no
	std::normal_distribution<double> dol{ 0, 1 };


	if (_timeGen + _lastGen <= _currentTime)
	{
		_lastGen = _currentTime;

		std::random_device r;
		std::default_random_engine gnd(r());
		for (auto i = 0; i < _num_particles; i++)
		{
			if (dol(gnd) > 0.75)
			{
				_particles.push_front(_model->clone());
				_particles.front()->pos.p += Vector3(_devTip_pos.x + _d(gnd), _devTip_pos.y + _d(gnd), _devTip_pos.z + _d(gnd));
				_particles.front()->vel += Vector3(_devTip_vel.x + _d(gnd), _devTip_vel.y + _d(gnd), _devTip_vel.z + _d(gnd));
			}
		}

		return _particles;
	}
	return _particles;
}
