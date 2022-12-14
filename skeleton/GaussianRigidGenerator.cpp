#include "GaussianRigidGenerator.h"

GaussianRigidGenerator::GaussianRigidGenerator(WorldManager* wm, Vector3 pos, Vector3 vel, double size,
	PxPhysics* phy, double t1, double n, Vector3 devTip_pos_Gau, Vector3 devTip_vel_Gau, double d_)
{
	d = d_;
	wm_ = wm;
	phy_ = phy;

	pos_ = pos;
	vel_ = vel;

	size_ = size;
	velR_ = 10;
	posR_ = 5;

	currentTime = 0;
	lSpawn = 0;
	tSpwan = t1;
	nSpawn = n;

	devTip_pos_Gau_ = devTip_pos_Gau;
	devTip_vel_Gau_ = devTip_vel_Gau;
}

list<PxRigidDynamic*> GaussianRigidGenerator::generate(double t)
{

	std::normal_distribution<double> _d{ 0, d };
	list<PxRigidDynamic*> d = list<PxRigidDynamic*>();
	currentTime += t;

	if (nM > currentN && lSpawn + tSpwan <= currentTime) {

		lSpawn = currentTime;
		currentN += nSpawn;

		std::default_random_engine rnd{ std::random_device{}() };
		std::uniform_real_distribution<double> posVar(-posR_, posR_);
		std::uniform_real_distribution<double> v(-velR_, velR_);

		for (auto i = 0; i < nSpawn; i++)
		{
			std::random_device r;
			std::default_random_engine gnd(r());

			Vector3 p = pos_ + Vector3(devTip_pos_Gau_.x + _d(gnd), devTip_pos_Gau_.x + _d(gnd),
				devTip_pos_Gau_.z + _d(gnd));
			Vector3 size = Vector3((double)size_, (double)size_, (double)size_);
			Vector3 velD = vel_ + Vector3(devTip_vel_Gau_.x + _d(rnd), devTip_vel_Gau_.y + _d(rnd),
				devTip_vel_Gau_.z + _d(rnd));

			d.push_front(phy_->createRigidDynamic(PxTransform(p)));

			d.front()->setLinearVelocity(velD);
			d.front()->setAngularVelocity({ 0,0,0 });

			auto shape = CreateShape(PxBoxGeometry(size)); 
			//auto shape = CreateShape(PxSphereGeometry(size_));

			d.front()->attachShape(*shape);

			d.front()->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });

			new RenderItem(shape, d.front(), { 1, 1, 0.2, 1 });

		}

	}

	return d;

}
