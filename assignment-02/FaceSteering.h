#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetRot, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	float mapToRange(float rotation);

private:
	const float TARGET_RADIUS = 1.0f;
	const float SLOW_RADIUS = 10.0f;
};
