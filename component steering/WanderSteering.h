#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	~WanderSteering() { delete mSubSteering; mSubSteering = nullptr; };
protected:
	virtual Steering* getSteering();
	void setNewTarget();
	Steering* mSubSteering;
	Vector2D getRandomPosition();
};
