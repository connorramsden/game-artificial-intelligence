#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();

private:
	float mTargetRadius = 1.0f;
	float mSlowRadius = 200.0f;
	float mTimeToTarget = 0.25f;
};
