#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
{
	mType = Steering::FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* FaceSteering::getSteering()
{
	float rotation;
	float rotationSize;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetRot = pTarget->getPositionComponent()->getFacing();
	}
	
	// Get naive direction to target
	rotation = mTargetRot - pOwner->getPositionComponent()->getFacing();
	rotation = mapToRange(rotation);
	rotationSize = abs(rotation);

	if (rotationSize < TARGET_RADIUS)
	{
		rotation = 0;
	}
	if (rotationSize > SLOW_RADIUS)
	{
		rotation = pOwner->getMaxRotVel();
	}
	else
	{
		rotation = pOwner->getMaxRotVel() / SLOW_RADIUS;
	}

	rotation *= rotation / rotationSize;

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.rotVel = rotation;
	// data.rotAcc = abs(data.rotVel);

	// if (data.rotAcc > data.maxRotAcc)
	// {
	// 	data.rotVel /= data.rotAcc;
	// 	data.rotVel *= pOwner->getMaxRotAcc();
	// }

	this->mData = data;
	return this;
}

float FaceSteering::mapToRange(float rotation)
{
	return float(rotation - (-PI) * floor(rotation / PI));
}
