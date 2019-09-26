#include "CohesionSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "SeekSteering.h"

CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering(Steering::COHESION, ownerID, targetLoc, targetID)
{
	mpSubSteeringSeek = new SeekSteering(mOwnerID, mTargetLoc, INVALID_UNIT_ID, false); 
	mOwnerNeighborhood = gpGame->getUnitManager()->getUnit(mOwnerID)->getNeighborhood();
}

Steering* CohesionSteering::getSteering()
{
	mOwnerNeighborhood = gpGame->getUnitManager()->getUnit(mOwnerID)->getNeighborhood();
	mpSubSteeringSeek->update();

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	calculateCenter(pOwner);

	setTargetLoc(mCommonPosition);

	mpSubSteeringSeek->setTargetLoc(mTargetLoc);

	PhysicsData seekData = mpSubSteeringSeek->getData();

	this->mData = seekData;

	return this;
}

void CohesionSteering::calculateCenter(Unit* pOwner)
{
	int centerDivisor = mOwnerNeighborhood.size() - 1;

	if (!mOwnerNeighborhood.empty())
	{
		for (int i = 0; i < centerDivisor; ++i)
		{
			mCommonPosition += mOwnerNeighborhood.at(i)->getPosition();
		}
	}

	mCommonPosition /= float(centerDivisor);
}
