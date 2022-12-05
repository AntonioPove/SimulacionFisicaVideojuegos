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

void WorldManager::update(double t)
{
	dfr->updateForces(t);
	exPrueba->updateConst(t);

}

void WorldManager::addForce()
{
	for (auto& e : _objects)
	{
		dfr->addRegistry(exPrueba, e);
	}
}


