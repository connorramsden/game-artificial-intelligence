#include "ArriveAndFaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"
#include "ArriveSteering.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
{
	mType = Steering::ARRIVE_AND_FACE;
	setOwnerID(ownerID);
	setTargetLoc(targetLoc);
	setTargetID(targetID);
}

Steering* ArriveAndFaceSteering::getSteering()
{
	mpSubSteeringArrive = new ArriveSteering(mOwnerID, mTargetLoc, mTargetID);
	mpSubSteeringFace = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	// update sub-steering systems
	mpSubSteeringArrive->update();
	mpSubSteeringFace->update();

	PhysicsData arriveData = mpSubSteeringArrive->getData();
	PhysicsData faceData = mpSubSteeringFace->getData();

	data.vel = arriveData.vel;
	data.acc = arriveData.acc;
	data.rotVel = faceData.rotVel;
	data.rotAcc = faceData.rotAcc;

	delete mpSubSteeringArrive;
	delete mpSubSteeringFace;

	this->mData = data;
	return this;
}
