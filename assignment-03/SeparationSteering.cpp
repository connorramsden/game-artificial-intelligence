#include "SeparationSteering.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include "SeekSteering.h"
#include <cmath>

SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering(Steering::SEPARATION, ownerID, targetLoc, targetID)
{
}

Steering* SeparationSteering::getSteering()
{
	mpSubSteeringFlee = new SeekSteering(mOwnerID, mTargetLoc, INVALID_UNIT_ID, true);

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	mpSubSteeringFlee->update();

	Vector2D commonPos = calculateCenter(pOwner);

	mpSubSteeringFlee->setTargetLoc(commonPos);

	this->mData = mpSubSteeringFlee->getData();

	delete mpSubSteeringFlee;

	return this;
}

Vector2D SeparationSteering::calculateCenter(Unit* pOwner)
{
	Vector2D avgPos = ZERO_VECTOR2D;

	list<Unit*> ownerNeighborhood = pOwner->getNeighborhood();

	if (ownerNeighborhood.empty())
		return avgPos;

	for (auto iter : ownerNeighborhood)
	{
		avgPos += (*iter).getPosition();
	}

	avgPos /= ownerNeighborhood.size() - 1;
	
	// Check that neither X or Y in average position is an infinite value
	// Weird bug I was having, not totally sure since this math seems right
	// So this is my way of correcting it, kinda hacky though.
	if (std::isinf(avgPos.getX()) || std::isinf(avgPos.getY()))
	{
		avgPos = Vector2D(0.0f, 0.0f);
	}

	return avgPos;
}
