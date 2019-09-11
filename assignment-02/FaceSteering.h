#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	float mapToRange(float angleOne, float angleTwo);

private:
	const float TARGET_RADIUS = 1.0f;
	const float SLOW_RADIUS = 10.0f;
};
