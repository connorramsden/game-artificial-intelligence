#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include "Component.h"
#include "Unit.h"

class PhysicsComponent;
class Steering;
enum Steering::SteeringType;

struct SteeringData : public Trackable
{
	SteeringData():type(Steering::INVALID_TYPE), targetLoc(ZERO_VECTOR2D), ownerID(INVALID_UNIT_ID), targetID(INVALID_UNIT_ID){};
	SteeringData(Steering::SteeringType theType, const Vector2D& theTargetLoc = ZERO_VECTOR2D, UnitID theOwner = INVALID_UNIT_ID, UnitID theTarget = INVALID_UNIT_ID)
		:type(theType), targetLoc(theTargetLoc), ownerID(theOwner), targetID(theTarget){};
	Steering::SteeringType type;
	Vector2D targetLoc;
	float targetRot;
	UnitID ownerID;
	UnitID targetID;
};

//const SteeringData ZERO_STEERING_DATA;

class SteeringComponent :public Component
{
public:
	//getters and setters
	Steering::SteeringType getType() const { return mData.type; };
	const Vector2D& getTargetLoc() const { return mData.targetLoc; };
	const float getTargetRot() const { return mData.targetRot; };
	UnitID getOwnerID() const { return mData.ownerID; };
	UnitID getTargetID() const { return mData.targetID; };
	ComponentID getPhysicsComponentID() const { return mPhysicsComponentID; };
	const SteeringData& getData() const { return mData; };
	void setData(const SteeringData& data);
	void setTargetLoc(const Vector2D& pos) { mData.targetLoc = pos; };
	void setTargetRot(const float rot) { mData.targetRot = rot; };
	void setTargetUnitID(const UnitID& id) { mData.targetID = id; };
	void applySteering(PhysicsComponent& physicsComponent);

	static const SteeringData& getZeroSteeringData() { static SteeringData data; return data; }
private:
	ComponentID mPhysicsComponentID;
	SteeringData mData;
	Steering* mpSteering;
	PhysicsComponent* mpPhysicsComponent=NULL;

	SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID);
	~SteeringComponent();
	void setPhysicsComponent(PhysicsComponent* pComp) { mpPhysicsComponent = pComp; };

	friend class ComponentManager;
};