#include "FlockingSteering.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "GroupAlignmentSteering.h"

FlockingSteering::FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
{
	mType = Steering::FLOCKING;
	setOwnerID(ownerID);
	setTargetLoc(targetLoc);
	setTargetID(targetID);

	mpSubSteeringCohesion = new CohesionSteering(mOwnerID, mTargetLoc, mTargetID);
	mpSubSteeringGroupAlignment = new GroupAlignmentSteering(Steering::GROUP_ALIGNMENT, mOwnerID, mTargetLoc, mTargetID);
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
}

Steering* FlockingSteering::getSteering()
{
	mpSubSteeringCohesion->update();
	mpSubSteeringGroupAlignment->update();

	Vector2D newTargetLoc = mpSubSteeringCohesion->getTargetLoc() + mpSubSteeringGroupAlignment->getTargetLoc();

	setTargetLoc(newTargetLoc);

	PhysicsData cohesionData = mpSubSteeringCohesion->getData();
	PhysicsData groupAlignData = mpSubSteeringGroupAlignment->getData();

	this->mData.vel = cohesionData.vel;
	this->mData.acc = cohesionData.acc;
	this->mData.rotVel = groupAlignData.rotVel;
	this->mData.rotAcc = groupAlignData.rotAcc;

	return this;
}