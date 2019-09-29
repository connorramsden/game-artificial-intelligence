#pragma once
#include <Trackable.h>
#include <DataRepository.h>
#include <string>

class DataLoader : public Trackable
{
public:
	DataLoader(const std::string& filename, DataRepository* pDepository);
	~DataLoader() {};
private:

};

//class only exists to hold a class level enum
class DataKeyEnum
{
public:
	enum DataKeyVals
	{
		TARGET_FPS,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		MAX_UNITS,
		MAX_ACC,
		MAX_SPEED,
		MAX_ROT_ACC,
		MAX_ROT_VEL,
		BACKGROUND_IMG,
		PLAYER_IMG,
		ENEMY_IMG,
		TARGET_IMG,
		GAME_FONT,
		NUM_UNITS_CREATE,
		SLOW_RADIUS_ARRIVE,
		TARGET_RADIUS_ARRIVE,
		TIME_TO_TARGET_ARRIVE,
		SLOW_RADIUS_FACE,
		TARGET_RADIUS_FACE,
		TIME_TO_TARGET_FACE,
		CHASE_DISTANCE,
		NEIGHBOR_RADIUS,
		COHESION_WEIGHT,
		SEPARATION_WEIGHT,
		ALIGN_WEIGHT
	};
};
