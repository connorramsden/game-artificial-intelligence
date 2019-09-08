#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, float targetRadius, float slowRadius, const UnitID& targetID)
{
	mType = Steering::ARRIVE;

	setOwnerID(ownerID);
	setTargetLoc(targetLoc);
	setTargetID(targetID);

	mTargetRadius = targetRadius;
	mSlowRadius = slowRadius;
}

Steering* ArriveSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	if (mTargetID != INVALID_UNIT_ID) {
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float distance = diff.getLength();

	if (distance < mTargetRadius)
		return nullptr;

	if (distance > mSlowRadius) {
		diff *= pOwner->getMaxAcc();
	}
	else {
		diff *= pOwner->getMaxAcc() * distance / mSlowRadius;
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;
	data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
