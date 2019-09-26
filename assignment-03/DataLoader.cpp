#include "DataLoader.h"
#include "DataRepository.h"
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

DataLoader::DataLoader(const string& filename, DataRepository* pRepository)
{
	ifstream input(filename);
	if (input.good())
	{
		while (!input.eof())
		{
			string line;
			getline(input, line);
			stringstream sstream(line);
			string id;
			sstream >> id;

			if (id == "screen_size")
			{
				UINT width, height;
				sstream >> width >> height;
				pRepository->addEntry(DataKeyEnum::SCREEN_WIDTH, width);
				pRepository->addEntry(DataKeyEnum::SCREEN_HEIGHT, height);
			}
			else if (id == "target_fps")
			{
				UINT fps;
				sstream >> fps;
				pRepository->addEntry(DataKeyEnum::TARGET_FPS, fps);
			}
			else if (id == "max_units")
			{
				UINT max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_UNITS, max);
			}
			else if (id == "unit_max_acc")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ACC, max);
			}
			else if (id == "unit_max_speed")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_SPEED, max);
			}
			else if (id == "unit_max_rot_acc")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ROT_ACC, max);
			}
			else if (id == "unit_max_rot_vel")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ROT_VEL, max);
			}
			else if (id == "background_image")
			{
				string fileName;
				sstream >> fileName;
				pRepository->addEntry(DataKeyEnum::BACKGROUND_IMG, fileName);
			}
			else if (id == "player_image")
			{
				string fileName;
				sstream >> fileName;
				pRepository->addEntry(DataKeyEnum::PLAYER_IMG, fileName);
			}
			else if (id == "enemy_image")
			{
				string fileName;
				sstream >> fileName;
				pRepository->addEntry(DataKeyEnum::ENEMY_IMG, fileName);
			}
			else if (id == "target_image")
			{
				string fileName;
				sstream >> fileName;
				pRepository->addEntry(DataKeyEnum::TARGET_IMG, fileName);
			}
			else if (id == "game_font")
			{
				string fileName;
				sstream >> fileName;
				pRepository->addEntry(DataKeyEnum::GAME_FONT, fileName);
			}
			else if (id == "num_units_create")
			{
				int unitsToCreate;
				sstream >> unitsToCreate;
				pRepository->addEntry(DataKeyEnum::NUM_UNITS_CREATE, unitsToCreate);
			}
			else if (id == "slow_radius_arrive")
			{
				float slowRadius;
				sstream >> slowRadius;
				pRepository->addEntry(DataKeyEnum::SLOW_RADIUS_ARRIVE, slowRadius);
			}
			else if (id == "target_radius_arrive")
			{
				float targetRadius;
				sstream >> targetRadius;
				pRepository->addEntry(DataKeyEnum::TARGET_RADIUS_ARRIVE, targetRadius);
			}
			else if (id == "time_to_target_arrive")
			{
				float timeToTarget;
				sstream >> timeToTarget;
				pRepository->addEntry(DataKeyEnum::TIME_TO_TARGET_ARRIVE, timeToTarget);
			}
			else if (id == "slow_radius_face")
			{
				float slowRadius;
				sstream >> slowRadius;
				pRepository->addEntry(DataKeyEnum::SLOW_RADIUS_FACE, slowRadius);
			}
			else if (id == "target_radius_face")
			{
			float targetRadius;
			sstream >> targetRadius;
			pRepository->addEntry(DataKeyEnum::TARGET_RADIUS_FACE, targetRadius);
			}
			else if (id == "time_to_target_face")
			{
			float timeToTarget;
			sstream >> timeToTarget;
			pRepository->addEntry(DataKeyEnum::TIME_TO_TARGET_FACE, timeToTarget);
			}
			else if (id == "chase_distance")
			{
				float chaseDistance;
				sstream >> chaseDistance;
				pRepository->addEntry(DataKeyEnum::CHASE_DISTANCE, chaseDistance);
			}
			else
			{
				cout << "Unknown tag:" << id << endl;
			}
		}
	}

}


