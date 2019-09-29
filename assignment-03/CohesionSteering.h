#include "Steering.h"

class Unit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc = ZERO_VECTOR2D, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringSeek;
	Vector2D calculateCenter(Unit* pOwner);
};
