#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();

private:
	float mTargetRadius;
	float mSlowRadius = 0.5f;
	float mTimeToTarget = 0.5f;
};
