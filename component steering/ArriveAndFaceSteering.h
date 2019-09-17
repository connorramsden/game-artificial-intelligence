#pragma once
#include "Steering.h"

class ArriveAndFaceSteering : public Steering
{
public:
	ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringArrive;
	Steering* mpSubSteeringFace;
};

