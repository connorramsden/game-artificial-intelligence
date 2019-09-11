#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();

private:
	const float TARGET_RADIUS = 1.0f;
	const float SLOW_RADIUS = 400.0f;
};
