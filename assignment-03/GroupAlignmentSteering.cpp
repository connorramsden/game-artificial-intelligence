#include "GroupAlignmentSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"

GroupAlignmentSteering::GroupAlignmentSteering(SteeringType type, const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering(Steering::GROUP_ALIGNMENT, ownerID, targetLoc, targetID)
{
	mpSubSteeringFace = new FaceSteering(Steering::FACE, ownerID, targetLoc); 
	mOwnerNeighborhood = gpGame->getUnitManager()->getUnit(mOwnerID)->getNeighborhood();
}

Steering* GroupAlignmentSteering::getSteering()
{
	mOwnerNeighborhood = gpGame->getUnitManager()->getUnit(mOwnerID)->getNeighborhood();
	mpSubSteeringFace->update();

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	calculateGroupFace(pOwner);

	setTargetLoc(mGroupFaceLoc);

	mpSubSteeringFace->setTargetLoc(mTargetLoc);

	PhysicsData faceData = mpSubSteeringFace->getData();

	this->mData = faceData;

	return this;
}

void GroupAlignmentSteering::calculateGroupFace(Unit* pOwner)
{
	int faceDivisor = mOwnerNeighborhood.size() - 1;

	if (!mOwnerNeighborhood.empty())
	{
		for (int i = 0; i < faceDivisor; ++i)
		{
			mGroupFaceLoc += mOwnerNeighborhood.at(i)->getHeadingVector();
		}
	}

	mGroupFaceLoc /= float(faceDivisor);
}
