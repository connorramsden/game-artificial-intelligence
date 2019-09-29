#include "Steering.h"

class Unit;

class FlockingSteering : public Steering
{
public:
	FlockingSteering(const UnitID& ownerID);
	~FlockingSteering();

protected:
	virtual Steering* getSteering();

	Steering* mpSubSteeringCohesion;
	Steering* mpSubSteeringSeparation;
	Steering* mpSubSteeringGroupAlignment;

private:
	float mCohesionWeight;
	float mSeparationWeight;
	float mAlignWeight;
};
