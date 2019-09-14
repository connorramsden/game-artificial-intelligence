#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	: Steering()
{
	mType = Steering::ARRIVE;

	setOwnerID(ownerID);
	setTargetLoc(targetLoc);
	setTargetID(targetID);
}

Steering* ArriveSteering::getSteering()
{
	Vector2D direction;
	Vector2D targetVel;
	float distance, targetSpeed;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	// Store Direction & Distance to the current target
	direction = mTargetLoc - pOwner->getPosition();
	distance = direction.getLength();

	// If we are already at our target, return nothing
	if (distance < TARGET_RADIUS)
		return nullptr;

	// If we are outside the slow radius, go maximum speed
	if (distance > SLOW_RADIUS)
	{
		targetSpeed = pOwner->getMaxSpeed();
	}
	// Otherwise, calculate a scaled speed
	else
	{
		targetSpeed = pOwner->getMaxSpeed() * distance / SLOW_RADIUS;
	}
	
	// targetVelocity = direction
	targetVel = direction;
	targetVel.normalize();
	targetVel *= targetSpeed;

	data.acc = targetVel - pOwner->getPhysicsComponent()->getVelocity();
	data.acc /= TIME_TO_TARGET;

	if (data.acc.getLength() > data.maxAccMagnitude)
	{
		data.acc.normalize();
		data.acc *= data.maxAccMagnitude;
	}
	
	data.rotAcc = 0.0f;

	this->mData = data;
	return this;
}
