/*
	Certification of Authenticity:
	I, Connor Ramsden, certify that this assignment is my own work.
*/

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include <sstream>

#include "Game.h"
#include <System.h>
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Font.h>
#include <FontManager.h>
#include <GraphicsBufferManager.h>
#include <InputSystem.h>
#include "GameMessageManager.h"
#include <Sprite.h>
#include "SpriteManager.h"
#include <Timer.h>
#include <DataRepository.h>
#include "PlayerMoveToMessage.h"
#include "UnitStateMessage.h"
#include "ExitMessage.h"
#include "WeightMessage.h"
#include "ComponentManager.h"
#include "UnitManager.h"
#include "DataLoader.h"
#include "ExtraColors.h"

Game* gpGame = NULL;

Game::Game()
	:Trackable("game class")
	, mpSystem(NULL)
	, mpGraphicsBufferManager(NULL)
	, mpSpriteManager(NULL)
	, mpFontManager(NULL)
	, mpLoopTimer(NULL)
	, mpMasterTimer(NULL)
	, mpFont(NULL)
	, mShouldExit(false)
	, mBackgroundBufferID("")
	, mpMessageManager(NULL)
	, mpComponentManager(NULL)
	, mpUnitManager(NULL)
	, mpRepository(NULL)
	, mTimeLastFrame(0.0f)
{}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	mpRepository = new DataRepository;
	DataLoader loader("data.txt", mpRepository);

	//create and init GraphicsSystem
	mpSystem = new System();
	bool goodGraphics = mpSystem->init(mpRepository->getEntry(DataKeyEnum::SCREEN_WIDTH).getUIntVal(), mpRepository->getEntry(DataKeyEnum::SCREEN_HEIGHT).getUIntVal());
	if (!goodGraphics)
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpSystem->getGraphicsSystem());
	mpSpriteManager = new SpriteManager;
	mpFontManager = new FontManager;

	mpMessageManager = new GameMessageManager();

	UINT maxUnits = mpRepository->getEntry(DataKeyEnum::MAX_UNITS).getUIntVal();
	mpComponentManager = new ComponentManager(maxUnits);
	mpUnitManager = new UnitManager(maxUnits);

	//load buffers
	GraphicsBuffer* pBuff;
	pBuff = mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, mpRepository->getEntry(DataKeyEnum::BACKGROUND_IMG).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID, mpRepository->getEntry(DataKeyEnum::PLAYER_IMG).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID, mpRepository->getEntry(DataKeyEnum::ENEMY_IMG).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mTargetBufferID, mpRepository->getEntry(DataKeyEnum::TARGET_IMG).getStringVal());

	//load Font
	mpFont = mpFontManager->createAndManageFont(COUR_24_FONT_ID, mpRepository->getEntry(DataKeyEnum::GAME_FONT).getStringVal(), 24);

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(mBackgroundBufferID);
	if (pBackGroundBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight());
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(mPlayerIconBufferID);
	Sprite* pArrowSprite = NULL;
	if (pPlayerBuffer != NULL)
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite(PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight());
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}
	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	if (pTargetBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	mTargetFPS = mpRepository->getEntry(DataKeyEnum::TARGET_FPS).getUIntVal();
	mTargetElapsedTime = 1000.0f / mTargetFPS;

	return true;
}

void Game::cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFontManager;
	mpFontManager = NULL;

	delete mpRepository;
	mpRepository = NULL;

	mpFont = NULL;

	//delete the graphics system
	delete mpSystem;
	mpSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;
}

void Game::doLoop()
{
	//game loop
	while (!mShouldExit)
	{
		gpPerformanceTracker->clearTracker("loop");
		gpPerformanceTracker->startTracking("loop");

		gpGame->beginLoop();

		gpPerformanceTracker->clearTracker("process");
		gpPerformanceTracker->startTracking("process");

		gpGame->processLoop();

		gpPerformanceTracker->stopTracking("process");

		gpGame->endLoop();

		gpPerformanceTracker->stopTracking("loop");
		std::cout << "loop took:" << gpPerformanceTracker->getElapsedTime("loop") << "ms    ";
		std::cout << "processing took:" << gpPerformanceTracker->getElapsedTime("process") << "ms\n";
		mTimeLastFrame = (float)gpPerformanceTracker->getElapsedTime("loop");
	}
}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

void Game::processLoop()
{
	InputSystem* pInputSystem = mpSystem->getInputSystem();

	float dt = (mTargetElapsedTime * mTimeMult) / 1000.0f;
	mpUnitManager->updateAll(dt);
	mpComponentManager->update(dt);
	pInputSystem->update(dt);
	
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	GraphicsSystem::draw(Vector2D(0, 0), *pBackgroundSprite);

	//draw units
	mpUnitManager->drawAll();

	if (mDrawDebugData)
	{
		drawDebugData();
	}

	mpSystem->getGraphicsSystem()->flip();

	Vector2D pos = pInputSystem->getCurrentMousePos();

	mpMessageManager->processMessagesForThisframe();

	if (pInputSystem->isMouseButtonPressed(InputSystem::LEFT))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::ESCAPE_KEY))
	{
		GameMessage* pMessage = new ExitMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::UP_KEY) && !mChangeWeights)
	{
		GameMessage* pMessage;

		if (mDoFleeBehaviour)
		{
			pMessage = new UnitStateMessage("create", Steering::SteeringType::SEEK);
		}
		else
		{
			pMessage = new UnitStateMessage("create", Steering::SteeringType::FLEE);
		}

		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (pInputSystem->isKeyPressed(InputSystem::DOWN_KEY) && !mChangeWeights)
	{
		GameMessage* pMessage = new UnitStateMessage("destroy");
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::LEFT_KEY))
	{
		mTimeMult -= 0.1f;
		if (mTimeMult < 0.0f)
			mTimeMult = 0.0f;
	}
	else if (pInputSystem->isKeyPressed(InputSystem::RIGHT_KEY))
	{
		mTimeMult += 0.1f;
	}
	else if (pInputSystem->isKeyPressed(InputSystem::SPACE_KEY))
	{
		mTimeMult = 1.0f;
	}

	if (pInputSystem->isKeyPressed(InputSystem::F_KEY))
	{
		mDoFleeBehaviour = true;
	}
	else
	{
		mDoFleeBehaviour = false;
	}

	if (pInputSystem->isKeyPressed(InputSystem::A_KEY))
	{
		GameMessage* pMessage = new UnitStateMessage("create", Steering::SteeringType::FLOCKING);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::M_KEY))
	{
		int numUnits = mpRepository->getEntry(DataKeyEnum::NUM_UNITS_CREATE).getIntVal();
		for (int i = 0; i < numUnits; ++i)
		{
			GameMessage* pMessage = new UnitStateMessage("create", Steering::SteeringType::WANDER_AND_CHASE);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
	}
	
	if (pInputSystem->isKeyPressed(InputSystem::X_KEY))
	{
		GameMessage* pMessage = new UnitStateMessage("destroy");
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	
	if (pInputSystem->isKeyPressed(InputSystem::C_KEY))
	{
		mChangeWeights = true;
		if (pInputSystem->isKeyPressed(InputSystem::UP_KEY))
		{
			GameMessage* pMessage = new WeightMessage("cu");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (pInputSystem->isKeyPressed(InputSystem::DOWN_KEY))
		{
			GameMessage* pMessage = new WeightMessage("cd");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		mpRepository->outputToFile("data.txt", mpRepository);
	}
	else if (pInputSystem->isKeyPressed(InputSystem::G_KEY))
	{
		mChangeWeights = true;
		if (pInputSystem->isKeyPressed(InputSystem::UP_KEY))
		{
			GameMessage* pMessage = new WeightMessage("gu");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (pInputSystem->isKeyPressed(InputSystem::DOWN_KEY))
		{
			GameMessage* pMessage = new WeightMessage("gd");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		mpRepository->outputToFile("data.txt", mpRepository);
	}
	else if (pInputSystem->isKeyPressed(InputSystem::S_KEY))
	{
		mChangeWeights = true;
		if (pInputSystem->isKeyPressed(InputSystem::UP_KEY))
		{
			GameMessage* pMessage = new WeightMessage("su");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (pInputSystem->isKeyPressed(InputSystem::DOWN_KEY))
		{
			GameMessage* pMessage = new WeightMessage("sd");
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		mpRepository->outputToFile("data.txt", mpRepository);
	}
	else
	{
		mChangeWeights = false;
	}

	if (pInputSystem->isKeyPressed(InputSystem::D_KEY))
	{
		mDrawDebugData = true;
	}
	else
	{
		mDrawDebugData = false;
	}
}

void Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed(mTargetElapsedTime);
}

void Game::drawDebugData()
{
	InputSystem* pInputSystem = mpSystem->getInputSystem();

	Vector2D pos = pInputSystem->getCurrentMousePos();

	//create mouse text
	std::stringstream textStream;
	textStream << pos;

	//write text at mouse position
	GraphicsSystem::writeText(pos, *mpFont, BLACK_COLOR, textStream.str(), Font::RIGHT);

	textStream.str("");
	textStream.clear();

	//write out current number of Units
	Uint32 numUnits = mpUnitManager->getNumUnits();
	textStream << "Units:" << numUnits;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth(), 0), *mpFont, BLACK_COLOR, textStream.str(), Font::RIGHT);

	textStream.str("");
	textStream.clear();

	//write out current fps
	int fps = (int)((1000.0f / mTimeLastFrame) + .5f);//+.5f does rounding
	textStream << "FPS:" << fps;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 2, 0), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);

	textStream.str("");
	textStream.clear();

	//write out time multiple
	textStream << "time mult:" << mTimeMult;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 4, 0), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);

	textStream.str("");
	textStream.clear();

	textStream << "Cohesion: " << mpRepository->getEntry(DataKeyEnum::COHESION_WEIGHT).getFloatVal();
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 4.0f, GraphicsSystem::getDisplayHeight() - 600.0f), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);

	textStream.str("");
	textStream.clear();

	textStream << "Align: " << mpRepository->getEntry(DataKeyEnum::ALIGN_WEIGHT).getFloatVal();
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 2.0f, GraphicsSystem::getDisplayHeight() - 600.0f), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);

	textStream.str("");
	textStream.clear();

	textStream << "Separation: " << mpRepository->getEntry(DataKeyEnum::SEPARATION_WEIGHT).getFloatVal();
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() - 100.0f, GraphicsSystem::getDisplayHeight() - 600.0f), *mpFont, BLACK_COLOR, textStream.str(), Font::RIGHT);
}

GraphicsSystem* Game::getGraphicsSystem() const
{
	return mpSystem->getGraphicsSystem();
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}
