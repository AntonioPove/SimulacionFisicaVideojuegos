#include "Ground.h"

Ground::Ground(Vector3 pos_) : pos(pos_)
{

	renderItem = new RenderItem(CreateShape(physx::PxSquareGeometry(6)),
		&pos, { 0.3, 0.5, 0.5, 1 });
}

Ground::~Ground()
{
}
