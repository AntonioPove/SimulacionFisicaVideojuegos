#include "WorldManager.h"

WorldManager::WorldManager(PxPhysics* gPhysics1, PxScene* gScene1)
{
	gPhysics = gPhysics1;
	gScene = gScene1;

	dfr = new DynamicsForceRegistry();
	exPrueba = new Explosion(500.0, 1000, 0, 0, 0);


}

WorldManager::~WorldManager()
{
	delete(item);
}

void WorldManager::addDynamicObject()
{

	object = gPhysics->createRigidDynamic(PxTransform({ 0, 10, 10 }));
	object->setLinearVelocity(vel);
	object->setAngularVelocity({ 0, 0, 0 });
	object->setMass(20);
	PxShape* shape = CreateShape(PxBoxGeometry(size));
	object->attachShape(*shape);
	object->setMassSpaceInertiaTensor({size.y * size.z , size.x * size.z, size.x * size.y});
	item = new RenderItem(shape, object, { 1, 0.8, 1, 1 });
	gScene->addActor(*object);

	_objects.push_back(object);
	
}

void WorldManager::addStaticObject()
{
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*suelo);

	PxRigidStatic* pared = gPhysics->createRigidStatic(PxTransform({ 10, 10, -30 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	pared->attachShape(*shape_suelo);
	item = new RenderItem(shape_suelo, pared, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*pared);
}

void WorldManager::addForce(std::list<PxRigidDynamic*> objects)
{
	for (auto e : objects) {
		gScene->addActor(*e);
		dfr->addRegistry(exPrueba, e);
	}
}

void WorldManager::createUniform()
{
	uniform = new UniformRigidGenerator(this, { 0, 0, 0 }, { 10, 50, 10 }, 1.5, gPhysics, 0.1, 5);
	uni = true;
}

void WorldManager::createGaussian()
{

	gaussian = new GaussianRigidGenerator(this, { 10, 10, 0 }, { 10, 10, 0 }, 1, gPhysics,
		0.1f, 2, { 0, 10, 0 }, { 0, 20, 0 }, 20);
	gau = true;
}

void WorldManager::update(double t)
{
	dfr->updateForces(t);
	exPrueba->updateConst(t);
	addForce(_objects);
	if (uni)
	addForce(uniform->generate(t));

	if(gau)
	addForce(gaussian->generate(t));
}


