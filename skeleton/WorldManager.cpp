#include "WorldManager.h"
#include "Player.h"


WorldManager::WorldManager(PxPhysics* gPhysics1, PxScene* gScene1)
{
	gPhysics = gPhysics1;
	gScene = gScene1;

	dfr = new DynamicsForceRegistry();
	exPrueba = new Explosion(500.0, 1000, 0, 0, 0);

	dragPrueba = new DragGenerator(0.01, 0.02);
	//wind_ = new UniformWindGenerator(0.01, 0.02, { 0, 0, -1 });

}

WorldManager::~WorldManager()
{
	for(auto e : _renderItems)
	{
		DeregisterRenderItem(e);
		delete(e);
	}
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
	_renderItems.push_back(item);
	_objects.push_back(object);
	
}

void WorldManager::addStaticObject()
{
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*suelo);

	PxRigidStatic* pared = gPhysics->createRigidStatic(PxTransform({ 10, 10, -30 }));
	PxShape* shape_suelo = CreateShape(PxBoxGeometry(40, 20, 5));
	pared->attachShape(*shape_suelo);
	item = new RenderItem(shape_suelo, pared, { 0.8, 0.8, 0.8, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared);
}

void WorldManager::addForce(std::list<PxRigidDynamic*> objects, bool insert)
{
	for (auto e : objects) {
		if(insert)
		gScene->addActor(*e);

		dfr->addRegistry(exPrueba, e);
		dfr->addRegistry(dragPrueba, e);
		//dfr->addRegistry(wind_, e);
	}
}

void WorldManager::addForce2(std::list<pair<PxRigidDynamic*, bool>> objectsD, bool insert)
{

	for (auto e : objectsD) {
		if (insert)
			gScene->addActor(*e.first);

		dfr->addRegistry(exPrueba, e.first);
		//dfr->addRegistry(dragPrueba, e);
		//dfr->addRegistry(wind_, e);
	}
}

PxRigidDynamic* WorldManager::createPlayer(Player* p)
{
	player_ = p;

	object = gPhysics->createRigidDynamic(PxTransform({ 120, 10, 180 }));
	object->setAngularVelocity({ 0, 0, 0 });
	object->setLinearVelocity({ 0, 0, 0 });
	PxShape* shape = CreateShape(PxSphereGeometry(10));
	object->attachShape(*shape);
	object->setMassSpaceInertiaTensor({ size.y * size.z , size.x * size.z, size.x * size.y });
	item = new RenderItem(shape, object, { 0.8, 0, 0.9, 1 });
	gScene->addActor(*object);
	_renderItems.push_back(item);
	_objects.push_back(object);
	return object;

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

void WorldManager::createMap()
{
	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(200, 0.1, 200));
	suelo->attachShape(*shape);
	item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*suelo);

	//Paredes lateral
	PxRigidStatic* pared1 = gPhysics->createRigidStatic(PxTransform({ 200, 0, 0 }));
	PxShape* shape_pared1 = CreateShape(PxBoxGeometry(5, 50, 200));
	pared1->attachShape(*shape_pared1);
	item = new RenderItem(shape_pared1, pared1, { 0, 0, 1, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared1);

	PxRigidStatic* pared2 = gPhysics->createRigidStatic(PxTransform({ -200, 0, 0 }));
	PxShape* shape_pared2 = CreateShape(PxBoxGeometry(5, 50, 200));
	pared2->attachShape(*shape_pared2);
	item = new RenderItem(shape_pared2, pared2, { 0, 0, 1, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared2);

	PxRigidStatic* pared3 = gPhysics->createRigidStatic(PxTransform({ 0, 0, -200 }));
	PxShape* shape_pared3 = CreateShape(PxBoxGeometry(200, 50, 5));
	pared3->attachShape(*shape_pared3);
	item = new RenderItem(shape_pared3, pared3, { 0, 1, 0, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared3);

	PxRigidStatic* pared4 = gPhysics->createRigidStatic(PxTransform({ 0, 0, 200 }));
	PxShape* shape_pared4 = CreateShape(PxBoxGeometry(200, 50, 5));
	pared4->attachShape(*shape_pared4);
	item = new RenderItem(shape_pared4, pared4, { 0, 1, 0, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared4);

	//Paredes Laberinto
	PxRigidStatic* pared5 = gPhysics->createRigidStatic(PxTransform({ 150, 0, 150 }));
	PxShape* shape_pared5 = CreateShape(PxBoxGeometry(50, 50, 5));
	pared5->attachShape(*shape_pared5);
	item = new RenderItem(shape_pared5, pared5, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared5);

	PxRigidStatic* pared6 = gPhysics->createRigidStatic(PxTransform({ 100, 0, 0 }));
	PxShape* shape_pared6 = CreateShape(PxBoxGeometry(100, 50, 5));
	pared6->attachShape(*shape_pared6);
	item = new RenderItem(shape_pared6, pared6, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared6);

	PxRigidStatic* pared7 = gPhysics->createRigidStatic(PxTransform({ 150, 0, -50 }));
	PxShape* shape_pared7 = CreateShape(PxBoxGeometry(50, 50, 5));
	pared7->attachShape(*shape_pared7);
	item = new RenderItem(shape_pared7, pared7, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared7);

	PxRigidStatic* pared8 = gPhysics->createRigidStatic(PxTransform({ -50, 0, 150 }));
	PxShape* shape_pared8 = CreateShape(PxBoxGeometry(5, 50, 50));
	pared8->attachShape(*shape_pared8);
	item = new RenderItem(shape_pared8, pared8, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared8);

	PxRigidStatic* pared9 = gPhysics->createRigidStatic(PxTransform({ 0, 0, -150 }));
	PxShape* shape_pared9 = CreateShape(PxBoxGeometry(100, 50, 5));
	pared9->attachShape(*shape_pared9);
	item = new RenderItem(shape_pared9, pared9, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared9);

	PxRigidStatic* pared10 = gPhysics->createRigidStatic(PxTransform({ -50, 0, 0 }));
	PxShape* shape_pared10 = CreateShape(PxBoxGeometry(5, 50, 50));
	pared10->attachShape(*shape_pared10);
	item = new RenderItem(shape_pared10, pared10, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared10);

	PxRigidStatic* pared11 = gPhysics->createRigidStatic(PxTransform({ 100, 0, 100 }));
	PxShape* shape_pared11 = CreateShape(PxBoxGeometry(5, 50, 50));
	pared11->attachShape(*shape_pared11);
	item = new RenderItem(shape_pared11, pared11, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared11);

	PxRigidStatic* pared12 = gPhysics->createRigidStatic(PxTransform({ -150, 0, 100 }));
	PxShape* shape_pared12 = CreateShape(PxBoxGeometry(50, 50, 5));
	pared12->attachShape(*shape_pared12);
	item = new RenderItem(shape_pared12, pared12, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared12);


	PxRigidStatic* pared13 = gPhysics->createRigidStatic(PxTransform({ -150, 0, -100 }));
	PxShape* shape_pared13 = CreateShape(PxBoxGeometry(50, 50, 5));
	pared13->attachShape(*shape_pared13);
	item = new RenderItem(shape_pared13, pared13, { 0.5, 0.2, 0.5, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*pared13);

}

void WorldManager::createBombs()
{
	object = gPhysics->createRigidDynamic(PxTransform({ 30, 0, 60 }));
	PxShape* shapeB1 = CreateShape(PxSphereGeometry(15));
	object->attachShape(*shapeB1);
	object->setMassSpaceInertiaTensor({ size.y * size.z , size.x * size.z, size.x * size.y });
	itemblue = new RenderItem(shapeB1, object, { 0.4, 0.18, 1, 1 });
	gScene->addActor(*object);
	_bombs.push_back({ object, true});

	object = gPhysics->createRigidDynamic(PxTransform({ -30, 0, -60 }));
	PxShape* shapeB2 = CreateShape(PxSphereGeometry(15));
	object->attachShape(*shapeB2);
	object->setMassSpaceInertiaTensor({ size.y * size.z , size.x * size.z, size.x * size.y });
	item = new RenderItem(shapeB2, object, { 1, 0.18, 0.4, 1 });
	gScene->addActor(*object);
	_renderItems.push_back(item);
	_bombs.push_back({ object, false });


	object = gPhysics->createRigidDynamic(PxTransform({ -130, 0, -170 }));
	PxShape* shapeB3 = CreateShape(PxSphereGeometry(15));
	object->attachShape(*shapeB3);
	object->setMassSpaceInertiaTensor({ size.y * size.z , size.x * size.z, size.x * size.y });
	item = new RenderItem(shapeB3, object, { 1, 0.18, 0.4, 1 });
	gScene->addActor(*object);
	_renderItems.push_back(item);
	_bombs.push_back({ object, false });


	object = gPhysics->createRigidDynamic(PxTransform({ 100, 0, -90 }));
	PxShape* shapeB4 = CreateShape(PxSphereGeometry(15));
	object->attachShape(*shapeB4);
	object->setMassSpaceInertiaTensor({ size.y * size.z , size.x * size.z, size.x * size.y });
	item = new RenderItem(shapeB4, object, { 1, 0.18, 0.4, 1 });
	gScene->addActor(*object);
	_renderItems.push_back(item);
	_bombs.push_back({ object, false });


}

void WorldManager::createFinal()
{
	final = gPhysics->createRigidStatic(PxTransform({ 150, 0.1, -150 }));
	PxShape* shapeM = CreateShape(PxBoxGeometry(43, 0.1, 43));
	final->attachShape(*shapeM);
	item = new RenderItem(shapeM, final, { 0, 1, 0, 1 });
	_renderItems.push_back(item);
	gScene->addActor(*final);
}

void WorldManager::update(double t)
{
	addForce(_objects, false);
	addForce2(_bombs, false);

	dfr->updateForces(t);
	exPrueba->updateConst(t);

	for (auto e : _bombs)
	{
		if (player_->collision(e.first->getGlobalPose()))
		{
			if(!e.second)
			player_->moveInicial();

			if (apagar && e.second)
			{
				dragPrueba->activate();
				apagar = false;

				DeregisterRenderItem(itemblue);
				delete(itemblue);
			}
		}
		
	}

	if (player_->final(final->getGlobalPose()))
	{
		player_->moveInicial();
		exPrueba->activate();
	}


	if (uni)
	addForce(uniform->generate(t), true);

	if(gau)
	addForce(gaussian->generate(t), true);


}





