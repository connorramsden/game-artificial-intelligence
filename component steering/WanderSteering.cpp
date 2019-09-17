
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "ArriveAndFaceSteering.h"
#include "GraphicsSystem.h"
#include <random>

WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) : Steering()
{
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetLoc(getRandomPosition());
	mpSubSteering = new ArriveAndFaceSteering(mOwnerID, mTargetLoc);
}

Steering* WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	PhysicsData arriveData = mpSubSteering->getData();

	// Update the sub-steering system
	mpSubSteering->update();
	
	if (Vector2D(mTargetLoc - pOwner->getPosition()).getLength() < 100.0f)
	{
		// Set the target location to a new random position
		setTargetLoc(getRandomPosition());
		// Update the sub-steering system to target the new location
		mpSubSteering->setTargetLoc(mTargetLoc);
	}

	// Update the sub-steering system
	mpSubSteering->update();

	PhysicsData subSteerData = mpSubSteering->getData();

	// Set this behaviour's data to the substeering system's data
	this->mData = arriveData;

	return this;
}

void WanderSteering::setNewTarget()
{
	setTargetLoc(getRandomPosition());
	mpSubSteering->setTargetLoc(mTargetLoc);
}

Vector2D WanderSteering::getRandomPosition()
{
	int posX = rand() % GraphicsSystem::getDisplayWidth();
	int posY = rand() % GraphicsSystem::getDisplayHeight();

	return Vector2D(posX, posY);
}
