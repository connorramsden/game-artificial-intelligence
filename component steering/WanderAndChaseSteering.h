#include "Steering.h"

class WanderAndChaseSteering : public Steering
{
public:
	WanderAndChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringMovement;
	Steering* mpSubSteeringFace;

private:
	float mChaseDistance;
};
