
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"
#include "ArriveSteering.h"
#include "GraphicsSystem.h"
#include <random>

WanderSteering::WanderSteering(const UnitID& ownerID) : Steering()
{
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetLoc(getRandomPosition());
	mSubSteering = new ArriveSteering(mOwnerID, mTargetLoc);
}

Steering* WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	PhysicsData arriveData = mSubSteering->getData();

	// Update the sub-steering system
	mSubSteering->update();
	
	if (Vector2D(mTargetLoc - pOwner->getPosition()).getLength() < 100.0f)
	{
		// Set the target location to a new random position
		setTargetLoc(getRandomPosition());
		// Update the sub-steering system to target the new location
		mSubSteering->setTargetLoc(mTargetLoc);
	}
	
	// Set this behaviour's data to the substeering system's data
	this->mData = arriveData;

	return this;
}

Vector2D WanderSteering::getRandomPosition()
{
	int posX = rand() % GraphicsSystem::getDisplayWidth();
	int posY = rand() % GraphicsSystem::getDisplayHeight();

	return Vector2D(posX, posY);
}
