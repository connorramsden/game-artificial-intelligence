#include "WanderAndChaseSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "WanderSteering.h"
#include "FaceSteering.h"
#include "SeekSteering.h"

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
{
	mType = Steering::WANDER_AND_CHASE;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mChaseDistance = gpGame->getDataRepository()->getEntry(DataKeyEnum::CHASE_DISTANCE).getFloatVal();
}

Steering* WanderAndChaseSteering::getSteering()
{
	Vector2D distance, tempLoc;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	PhysicsData movementData, faceData;
	
	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		tempLoc = pTarget->getPosition();
	}

	distance = tempLoc - pOwner->getPosition();

	if (distance.getLength() > mChaseDistance)
	{
		mpSubSteeringMovement = new WanderSteering(mOwnerID, mTargetLoc, INVALID_UNIT_ID);
		mpSubSteeringFace = new FaceSteering(mOwnerID, mTargetLoc, INVALID_UNIT_ID);
	}
	else
	{
		setTargetLoc(tempLoc);
		mpSubSteeringMovement = new SeekSteering(mOwnerID, mTargetLoc, mTargetID);
		mpSubSteeringFace = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	}

	mpSubSteeringMovement->update();
	mpSubSteeringFace->update();

	movementData = mpSubSteeringMovement->getData();
	faceData = mpSubSteeringFace->getData();

	data.acc = movementData.acc;
	data.vel = movementData.vel;
	data.rotVel = faceData.rotVel;
	data.rotAcc = faceData.rotAcc;

	delete mpSubSteeringMovement;
	delete mpSubSteeringFace;

	this->mData = data;
	return this;
}