#pragma once
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID);
protected:
	virtual Steering* getSteering();

private:
	float mWanderOffset, mWanderRadius, mWanderRate, mWanderOrientation;
};

