#include "Steering.h"

class Unit;

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID);
	~FlockingSteering();

protected:
	virtual Steering* getSteering();

	Steering* mpSubSteeringCohesion;
	Steering* mpSubSteeringSeparation;
	Steering* mpSubSteeringGroupAlignment;
};
