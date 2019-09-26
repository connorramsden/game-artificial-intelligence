#include "Steering.h"

using std::vector;
class Unit;

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(SteeringType type, const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID);
	~GroupAlignmentSteering() { delete mpSubSteeringFace; };
protected:
	Steering* getSteering();
	void calculateGroupFace(Unit* pOwner);
private:
	Steering* mpSubSteeringFace;
	Vector2D mGroupFaceLoc;
	vector<Unit*> mOwnerNeighborhood;
};
