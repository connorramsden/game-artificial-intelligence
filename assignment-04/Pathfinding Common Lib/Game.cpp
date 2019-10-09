
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include <System.h>
#include <InputSystem.h>
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <GraphicsBufferManager.h>
#include <Sprite.h>
#include <SpriteManager.h>
#include <FontManager.h>
#include <System.h>
#include <Timer.h>
#include <Defines.h>

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpFontManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mLoopTargetTime(0.0f)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	srand((unsigned int)time(0));//seed random number generator

	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	mpSystem = new System;
	mpSystem->init(WIDTH, HEIGHT);

	mpGraphicsBufferManager = new GraphicsBufferManager(getGraphicsSystem());
	mpSpriteManager = new SpriteManager;
	mpFontManager = new FontManager;

	mpFontManager->createAndManageFont(COUR_20_FONT_ID, "cour.ttf", 20);

	return true;
}

void Game::cleanup()
{
	delete mpFontManager;
	mpFontManager = NULL;

	delete mpSpriteManager;
	mpSpriteManager = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;

	delete mpSystem;
	mpSystem = NULL;

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

}

void Game::beginLoop()
{
	mpLoopTimer->start();

	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	GraphicsSystem::draw(ZERO_VECTOR2D, *pBackgroundSprite);
}

void Game::processLoop()
{
		getGraphicsSystem()->flip();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( mLoopTargetTime );
	return mShouldExit;
}


float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

float mapRotationToRange( float rotation, float low, float high )
{
	while( rotation < low )
	{
		rotation += ( 2.0f * (float)PI );
	}

	while( rotation > high )
	{
		rotation -= ( 2.0f * (float)PI );
	}
	return rotation;
}
