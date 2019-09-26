#include "Steering.h"

class FaceSteering :public Steering
{
public:
	FaceSteering(SteeringType type, const UnitID& ownerID, const Vector2D& targetLoc);

	double static calcFacingDiff(double facing, double targetFacing);
	bool isTargetToRight();

protected:
	Steering* getSteering();
};
