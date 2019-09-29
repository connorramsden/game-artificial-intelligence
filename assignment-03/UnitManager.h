#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <unordered_map>
#include "PositionComponent.h"
#include "PhysicsComponent.h"

#include "Unit.h"

#include <list>
using std::list;

class Unit;
class Sprite;
class Steering;
enum Steering::SteeringType;
struct PositionData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;

class UnitManager : public Trackable
{
public:
	UnitManager(Uint32 maxSize);
	~UnitManager() {};

	Unit* createUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = PositionComponent::getZeroPositionData(), const PhysicsData& physicsData = PhysicsComponent::getZeroPhysicsData(), const UnitID& id = INVALID_UNIT_ID);
	Unit* createPlayerUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = PositionComponent::getZeroPositionData(), const PhysicsData& physicsData = PhysicsComponent::getZeroPhysicsData());
	Unit* createRandomUnit(const Sprite& sprite, Steering::SteeringType unitBehaviour);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();

	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };

	Uint32 getNumUnits() const { return mUnitMap.size(); };

protected:
	// Create a linked-list 'neighborhood'
	list<Unit*> createNeighborhood(const Vector2D& centerLoc);
private:
	int mCounter = 0;
	float mNeighborhoodRadius;
	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::unordered_map<UnitID, Unit*> mUnitMap;
};
