#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"

class Ground
{
public:
	Ground(Vector3 pos);
	~Ground();

protected:
	RenderItem* renderItem;
	physx::PxTransform pos;

};

