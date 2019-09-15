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
	mSubSteering = new ArriveAndFaceSteering(mOwnerID, mTargetLoc);
}

Steering* WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	if (Vector2D(mTargetLoc - pOwner->getPosition()).getLength() < 100.0f)
	{
		setNewTarget();
	}

	// Update the sub-steering system
	mSubSteering->update();

	PhysicsData subSteerData = mSubSteering->getData();

	// Set this behaviour's data to the substeering system's data
	this->mData = subSteerData;

	return this;
}

void WanderSteering::setNewTarget()
{
	setTargetLoc(getRandomPosition());
	mSubSteering->setTargetLoc(mTargetLoc);
}

Vector2D WanderSteering::getRandomPosition()
{
	int posX = rand() % GraphicsSystem::getDisplayWidth();
	int posY = rand() % GraphicsSystem::getDisplayHeight();

	return Vector2D(posX, posY);
}
