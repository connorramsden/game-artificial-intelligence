#include "Steering.h"

class ArriveAndFaceSteering : public Steering
{
public:
	ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	~ArriveAndFaceSteering() { cleanUp(); };
	void cleanUp();

protected:
	virtual Steering* getSteering();
	void resetTarget(const Vector2D& loc);
	Steering* mSubSteeringArrive;
	Steering* mSubSteeringFace;
};

