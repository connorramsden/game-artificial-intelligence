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
	mSubSteeringArrive = new ArriveSteering(ownerID, targetLoc, targetID);
	mSubSteeringFace = new FaceSteering(ownerID, targetLoc, targetID);
}

void ArriveAndFaceSteering::cleanUp()
{
	delete mSubSteeringArrive;
	mSubSteeringArrive = nullptr;
	delete mSubSteeringFace;
	mSubSteeringFace = nullptr;
}

Steering* ArriveAndFaceSteering::getSteering()
{
	mSubSteeringArrive = new ArriveSteering(mOwnerID, mTargetLoc, mTargetID);
	mSubSteeringFace = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	// update sub-steering systems
	mSubSteeringArrive->update();
	mSubSteeringFace->update();

	PhysicsData arriveData = mSubSteeringArrive->getData();
	PhysicsData faceData = mSubSteeringFace->getData();

	data.vel = arriveData.vel;
	data.acc = arriveData.acc;
	data.rotVel = faceData.rotVel;
	data.rotAcc = faceData.rotAcc;

	this->mData = data;
	return this;
}