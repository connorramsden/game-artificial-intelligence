#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	: Steering()
{
	mType = Steering::FACE;

	mSlowRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::SLOW_RADIUS_FACE).getFloatVal();
	mTargetRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::TARGET_RADIUS_FACE).getFloatVal();
	mTimeToTarget = gpGame->getDataRepository()->getEntry(DataKeyEnum::TIME_TO_TARGET_FACE).getFloatVal();

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

// Borrowed faceSteering math from:
// https://github.com/Jagman926/MontrealAIForGames/blob/FlockingBranch/GameAI/component%20steering%20SDL/FaceSteering.cpp
// Lines 32 - 39
Steering* FaceSteering::getSteering()
{
	Vector2D diff;
	float targetRotation, rotation, rotationSize, mappedRotation;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	// Start Borrowed Math
	diff = mTargetLoc - pOwner->getPosition();
	float targetOrientation = atan2(diff.getX(), -diff.getY()); // this line is changed from the above link, due to the link's math not working the right way

	rotation = targetOrientation - pOwner->getFacing();

	mappedRotation = float(mapToRangeMinusPiToPi(rotation));
	rotationSize = abs(mappedRotation);
	// End Borrowed Math

	// Formula from pg. 64 & 65 in the textbook
	// Start Book Formula
	if (rotationSize < mTargetRadius)
		targetRotation = 0.0f;
	if (rotationSize > mSlowRadius)
	{
		targetRotation = pOwner->getMaxRotAcc();
	}
	else
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / mSlowRadius;

	targetRotation *= rotation / rotationSize;

	data.rotAcc = targetRotation - pOwner->getPhysicsComponent()->getRotationalVelocity();
	data.rotAcc /= mTimeToTarget;

	float angularAcceleration = abs(pOwner->getPhysicsComponent()->getRotationalAcceleration());
	if (angularAcceleration > pOwner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= pOwner->getMaxRotAcc();
	}
	// End Book Formula

	data.vel = 0.0f;
	data.acc = 0.0f;

	this->mData = data;

	return this;
}