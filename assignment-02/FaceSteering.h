#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	float mapToRange(float rotation);

private:
	const float TARGET_RADIUS = 0.1f;
	const float SLOW_RADIUS = 0.5f;
	const float TIME_TO_TARGET = 0.5f;
};
