#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "ArriveSteering.h"
#include "GraphicsSystem.h"
#include <random>

WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) : Steering()
{
	mType = Steering::WANDER;
	setOwnerID(ownerID);
	setTargetLoc(getRandomPosition());
	setTargetID(targetID);
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	
	if (mTargetID != INVALID_UNIT_ID)
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != nullptr);
		mTargetLoc = pTarget->getPosition();
	}

	mpSubSteering = new ArriveSteering(mOwnerID, mTargetLoc, mTargetID);
	mpSubSteering->update();

	if (Vector2D(mTargetLoc - pOwner->getPosition()).getLength() < 100.0f)
	{
		setNewTarget();
	}

	PhysicsData arriveData = mpSubSteering->getData();

	// Set this behaviour's data to the substeering system's data
	this->mData = arriveData;

	delete mpSubSteering;

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
