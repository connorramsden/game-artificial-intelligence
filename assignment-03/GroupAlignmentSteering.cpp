#include "GroupAlignmentSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"

GroupAlignmentSteering::GroupAlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering(Steering::GROUP_ALIGNMENT, ownerID, targetLoc, targetID)
{}

Steering* GroupAlignmentSteering::getSteering()
{
	mpSubSteeringFace = new FaceSteering(Steering::FACE, mOwnerID, mTargetLoc);

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	Vector2D commonFace = calculateGroupFace(pOwner);

	mpSubSteeringFace->setTargetLoc(commonFace);

	this->mData = mpSubSteeringFace->getData();

	delete mpSubSteeringFace;

	return this;
}

Vector2D GroupAlignmentSteering::calculateGroupFace(Unit* pOwner)
{
	Vector2D avgFace = ZERO_VECTOR2D;

	list<Unit*> ownerNeighborhood = pOwner->getNeighborhood();

	// If the neighborhood is empty, return ZERO_VECTOR2D
	if (ownerNeighborhood.empty())
		return avgFace;

	for (auto iter : ownerNeighborhood)
	{
		avgFace += (*iter).getHeadingVector();
	}
	
	// Check that neither X or Y in average position is an infinite value
	// Weird bug I was having, not totally sure since this math seems right
	// So this is my way of correcting it, kinda hacky though.
	if (std::isinf(avgFace.getX()) || std::isinf(avgFace.getY()))
	{
		avgFace = Vector2D(0.0f, 0.0f);
	}

	avgFace /= ownerNeighborhood.size() - 1;

	return avgFace;
}
