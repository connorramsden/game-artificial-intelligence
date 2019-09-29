#include "Steering.h"

class Unit;

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(const UnitID& ownerID, const Vector2D& targetLoc = ZERO_VECTOR2D, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringFace;
	Vector2D calculateGroupFace(Unit* pOwner);
};
