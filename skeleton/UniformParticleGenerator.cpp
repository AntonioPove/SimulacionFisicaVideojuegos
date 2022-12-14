#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(ParticleSystem* s, std::string name, Particle* p, int n, 
	Vector3 pos, Vector3 v) : ParticleGenerator(name, p, n, pos, v, s)
{
	_vel_width = v;
	_pos_width = pos;
}

std::list<Particle*> UniformParticleGenerator::generateParticles(double t)
{

	std::uniform_real_distribution<> pos(0.0, 10.0);
	std::uniform_real_distribution<> vel(0.0, 10.0);


	auto rnd = rand() % 100;

	_currentTime += t;
	std::list<Particle*> _particles = std::list<Particle*>();

	if (_timeGen + _lastGen <= _currentTime)
	{
		_lastGen = _currentTime;

		std::random_device rd;  
		std::mt19937 gen(rd());
		for (auto i = 0; i < _num_particles; i++)
		{
			if (rnd < 80)
			{
				_particles.push_front(_model->clone());
				_particles.front()->pos.p += Vector3((float)_pos_width.x * pos(gen), (float)_pos_width.y * pos(gen),
					(float)_pos_width.z * pos(gen));
				_particles.front()->vel += Vector3((float)_vel_width.x * vel(gen), (float)_vel_width.y * vel(gen),
					(float)_vel_width.z * vel(gen));
			}
		}

		return _particles;
	}
	return _particles;
}
