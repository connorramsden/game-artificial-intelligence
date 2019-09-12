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

	diff = mTargetLoc - pOwner->getPosition();
	float targetOrientation = atan2(diff.getX(), -diff.getY());

	rotation = targetOrientation - pOwner->getFacing();

	mappedRotation = mapToRange(rotation);
	rotationSize = abs(mappedRotation);

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
	 	
	this->mData = data;

	return this;
}

float FaceSteering::mapToRange(float rotation)
{
	float convertedRotation;
	convertedRotation = fmod((rotation), 2.0f * PI);

	if (convertedRotation > PI)
		convertedRotation = (convertedRotation - PI) * -1.0f;
	else if (convertedRotation < -PI)
		convertedRotation = (convertedRotation + PI) * -1.0f;

	return convertedRotation;
}
