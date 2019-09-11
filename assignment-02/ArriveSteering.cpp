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
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);	

	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
		targetVel = pTarget->getPhysicsComponent()->getVelocity();
	}

	// Store Direction & Distance to the current target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float distance = direction.getLength();

	// If we are already at our target, return nothing
	if (distance < TARGET_RADIUS)
		direction = 0;

	// If we are outside the slow radius, go maximum speed
	if (distance > SLOW_RADIUS)
	{
		direction *= pOwner->getMaxSpeed();
	}
	// Otherwise, calculate a scaled speed
	else
	{
		direction *= pOwner->getMaxSpeed() * distance / SLOW_RADIUS;
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	// targetVelocity = direction
	data.vel = direction;

	data.acc = targetVel - data.vel;
	data.acc /= mTimeToTarget;
	
	if (data.acc.getLength() > pOwner->getMaxAcc()) {
		data.acc.normalize();
		data.acc *= pOwner->getMaxAcc();
	}
	
	data.rotVel = 0.0f;
	data.rotAcc = 0.0f;

	this->mData = data;
	return this;
}
