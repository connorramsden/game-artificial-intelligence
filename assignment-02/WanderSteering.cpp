
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"

WanderSteering::WanderSteering(const UnitID& ownerID) : Steering()
{
	mType = Steering::WANDER;

	setOwnerID(ownerID);
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	// Step 01: Calculate the target to delegate to face

	// Step 02: Delegate to face

	// Step 03: Set linear acceleration to be at full.	

	return this;
}
