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
	Vector2D rotation;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}
	
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	this->mData = data;

	return this;
}

float FaceSteering::mapToRange(float angleOne, float angleTwo)
{
	float distance = angleOne - angleTwo;
	return fmod(distance + PI, 2.0f * PI) - PI;
}
