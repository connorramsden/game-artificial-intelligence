#include "Steering.h"

class Unit;
using std::vector;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	~CohesionSteering() { delete mpSubSteeringSeek; }
protected:
	virtual Steering* getSteering();
	Steering* mpSubSteeringSeek;
	void calculateCenter(Unit* pOwner);

private:
	Vector2D mCommonPosition; 
	vector<Unit*> mOwnerNeighborhood;
};
