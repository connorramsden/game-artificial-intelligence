#pragma once
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID);
	~WanderSteering() { delete mSubSteering; mSubSteering = nullptr; };
protected:
	virtual Steering* getSteering();
	Steering* mSubSteering;
	Vector2D getRandomPosition();

private:
	float mWanderOffset, mWanderRadius, mWanderRate, mWanderOrientation;
};

