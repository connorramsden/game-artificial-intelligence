#include "FlockingSteering.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "GroupAlignmentSteering.h"

FlockingSteering::FlockingSteering(const UnitID& ownerID)
	:Steering(Steering::FLOCKING)
{
	setOwnerID(ownerID);
	mCohesionWeight = gpGame->getDataRepository()->getEntry(DataKeyEnum::COHESION_WEIGHT).getFloatVal();
	mSeparationWeight = gpGame->getDataRepository()->getEntry(DataKeyEnum::SEPARATION_WEIGHT).getFloatVal();
	mAlignWeight = gpGame->getDataRepository()->getEntry(DataKeyEnum::ALIGN_WEIGHT).getFloatVal();
	mpSubSteeringCohesion = new CohesionSteering(mOwnerID);
	mpSubSteeringSeparation = new SeparationSteering(mOwnerID);
	mpSubSteeringGroupAlignment = new GroupAlignmentSteering(mOwnerID);
}

FlockingSteering::~FlockingSteering()
{
	if (mpSubSteeringCohesion != nullptr)
	{
		delete mpSubSteeringCohesion;
		mpSubSteeringCohesion = nullptr;
	}

	if (mpSubSteeringGroupAlignment != nullptr)
	{
		delete mpSubSteeringGroupAlignment;
		mpSubSteeringGroupAlignment = nullptr;
	}

	if (mpSubSteeringSeparation != nullptr)
	{
		delete mpSubSteeringSeparation;
		mpSubSteeringSeparation = nullptr;
	}
}

Steering* FlockingSteering::getSteering()
{
	// Since values can be tweaked during gameplay, re-get them
	DataRepository* tempRepo = gpGame->getDataRepository();
	mCohesionWeight = tempRepo->getEntry(DataKeyEnum::COHESION_WEIGHT).getFloatVal();
	mSeparationWeight = tempRepo->getEntry(DataKeyEnum::SEPARATION_WEIGHT).getFloatVal();
	mAlignWeight = tempRepo->getEntry(DataKeyEnum::ALIGN_WEIGHT).getFloatVal();

	// Establish data for THIS unit
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData ownerData = pOwner->getPhysicsComponent()->getData();
	
	// Update the data for the Cohesion sub-steering
	mpSubSteeringCohesion->update();
	mpSubSteeringGroupAlignment->update();
	mpSubSteeringSeparation->update();

	PhysicsData cohesionData = mpSubSteeringCohesion->getData();
	PhysicsData alignData = mpSubSteeringGroupAlignment->getData();
	PhysicsData sepData = mpSubSteeringSeparation->getData();

	// Grab a target position from the sub steering
	Vector2D targetPos = mpSubSteeringCohesion->getTargetLoc() + mpSubSteeringGroupAlignment->getTargetLoc();
		
	setTargetLoc(targetPos);

	ownerData.vel = (cohesionData.vel * mCohesionWeight) + (alignData.vel * mCohesionWeight) + (sepData.vel * mSeparationWeight);
	ownerData.acc = (cohesionData.acc * mCohesionWeight) + (alignData.acc * mCohesionWeight) + (sepData.acc * mSeparationWeight);
	ownerData.rotVel = (cohesionData.rotVel * mCohesionWeight) + (alignData.rotVel * mCohesionWeight) + (sepData.rotVel * mSeparationWeight);
	ownerData.rotAcc = (cohesionData.rotAcc * mCohesionWeight) + (alignData.rotAcc * mCohesionWeight) + (sepData.rotAcc * mSeparationWeight);
	
	this->mData = ownerData;

	return this;
}