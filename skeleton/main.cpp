#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Particle.h"
#include "Proyectil.h"

#include "ParticleSystem.h"
#include "ParticleGenerator.h"

#include <iostream>
#include <vector>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Particle* particle = NULL;
Proyectil* proyectil = NULL;

std::vector<Proyectil*> particles;

RenderItem* ground = NULL;
RenderItem* diana = NULL;

ParticleSystem* ps;
GaussianParticleGenerator* pg;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	ps = new ParticleSystem();


	
	//particle = new Particle({ 0, 10, 0 }, { 0, 10, 0 }, 6, {0, -2, 0}, 0.99);
	//ground = new RenderItem(CreateShape(PxBoxGeometry(100, 1, 100)),
	//	new PxTransform(0, -5, 20), { 1,1,1,1 });

	//diana = new RenderItem(CreateShape(PxBoxGeometry(10, 10, 10)),
	//	new PxTransform(10, 100, 10), { 1,0.5,0.5,1 });

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	////particle->integrate(t);
	//for (int i = 0; i < particles.size(); i++)
	//{
	//	particles[i]->integrate(t);

	//}

	ps->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete ps;
	}



// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'B':
	{
		//particles.push_back(new Proyectil(GetCamera()->getEye(), 200, 3, 20, 10000));
		break;
	}
	case 'G':
	{
		ps->addParticleGenerator(ParticleSystem::Gau, { 10, 10, 10 }, { 1, 1, 0 }, 4);
		break;
	}
	case 'U':
	{
		ps->addParticleGenerator(ParticleSystem::Uni, { 1, 1, 1 }, { 0, 10, 0 }, 4);
		break;
	}
	case 'L':
	{
		ps->addParticleGenerator(ParticleSystem::Uni, { 10, 50, 10 }, { 0, 0, 0 }, 1);
		break;
	}
	case '1':
	{
		ps->createFireworkSystem(1);
		break;
	}
	case '2':
	{
		ps->createFireworkSystem(2);
		break;
	}
	case '3':
	{
		ps->createFireworkSystem(3);
		break;
	}
	case 'Q':
	{
		ps->destroy();
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}