#include "CohesionSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "SeekSteering.h"
#include <cmath>

CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering(Steering::COHESION, ownerID, targetLoc, targetID)
{}

Steering* CohesionSteering::getSteering()
{
	mpSubSteeringSeek = new SeekSteering(mOwnerID, mTargetLoc);
	
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	mpSubSteeringSeek->update();

	Vector2D commonPos = calculateCenter(pOwner);

	mpSubSteeringSeek->setTargetLoc(commonPos);

	this->mData = mpSubSteeringSeek->getData();

	delete mpSubSteeringSeek;

	return this;
}

Vector2D CohesionSteering::calculateCenter(Unit* pOwner)
{
	Vector2D avgPos = ZERO_VECTOR2D;

	list<Unit*> ownerNeighborhood = pOwner->getNeighborhood();

	// If the neighborhood is empty, return ZERO_VECTOR2D
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
