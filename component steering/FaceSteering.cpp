#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	: Steering()
{
	mType = Steering::FACE;

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

	mappedRotation = float( mapToRangeMinusPiToPi(rotation));
	rotationSize = abs(mappedRotation);
	// End Borrowed Math

	// Formula from pg. 64 & 65 in the textbook
	// Start Book Formula
	if (rotationSize < TARGET_RADIUS)
		targetRotation = 0.0f;
	if (rotationSize > SLOW_RADIUS)
	{
		targetRotation = pOwner->getMaxRotAcc();
	}
	else
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / SLOW_RADIUS;

	targetRotation *= rotation / rotationSize;

	data.rotAcc = targetRotation - pOwner->getPhysicsComponent()->getRotationalVelocity();
	data.rotAcc /= TIME_TO_TARGET;

	float angularAcceleration = abs(pOwner->getPhysicsComponent()->getRotationalAcceleration());
	if (angularAcceleration > pOwner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= pOwner->getMaxRotAcc();
	}
	// End Book Formula

	data.acc = 0.0f;

	this->mData = data;

	return this;
}