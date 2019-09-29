#include "Steering.h"

class Unit;

class SeparationSteering : public Steering
{
public:
	SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc = ZERO_VECTOR2D, const UnitID& targetID = INVALID_UNIT_ID);
protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringFlee;
	Vector2D calculateCenter(Unit* pOwner);
};