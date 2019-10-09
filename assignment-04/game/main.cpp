/*main.cpp
 *
 *	Dean Lawson
 *	Champlain College
 *	2019
 *
 */

#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include <Game.h>
#include "GameApp.h"
#include <GraphicsSystem.h>
#include <GraphicsBufferManager.h>
#include <GraphicsBuffer.h>
#include <InputSystem.h>
#include <Sprite.h>
#include <Timer.h>
#include <MemoryTracker.h>
#include <PerformanceTracker.h>
#include <EventSystem.h>

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{

	EventSystem::initInstance();

	gpPerformanceTracker = new PerformanceTracker();

	gpGame = new GameApp();

	gpGame->init();

	bool shouldExit = false;

	while( !shouldExit )
	{
		//if escape key was down then exit the loop
		if (gpGame->getInputSystem()->isKeyPressed(InputSystem::ESCAPE_KEY))
		{
			gpGame->markForExit();
		}

		gpGame->beginLoop();
		gpGame->processLoop();
		shouldExit = gpGame->endLoop();
	}

	//cleanup
	gpGame->cleanup();
	delete gpGame;
	delete gpPerformanceTracker;

	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations( std::cout );

	system("pause");

	return 0;
}

