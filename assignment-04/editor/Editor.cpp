#include <fstream>

#include <Game.h>
#include "Editor.h"
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <GraphicsBufferManager.h>
#include <Grid.h>
#include <GridVisualizer.h>
#include <Sprite.h>
#include <SpriteManager.h>
#include <Vector2D.h>
#include <InputSystem.h>

using namespace std;

const int GRID_SIZE_X = 32;
const int GRID_SIZE_Y = 32;
const GraphicsBufferID BACKGROUND_ID = "Background";
const std::string gFileName = "..\\pathgrid.txt";


Editor::Editor()
:Game()
,mpGrid(NULL)
,mpGridVisualizer(NULL)
{
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	GraphicsSystem* pGraphicsSystem = getGraphicsSystem();

	//create and load the Grid, GridBuffer, and GridVisualizer
	mpGrid = new Grid(pGraphicsSystem->getDisplayWidth(), pGraphicsSystem->getDisplayHeight(), GRID_SIZE_X, GRID_SIZE_Y);
	mpGridVisualizer = new GridVisualizer(mpGrid);
	std::ifstream theStream(gFileName);
	if (theStream.good())//file found
	{
		mpGrid->load(theStream);
	}
	else//file missing
	{
		int numGridCells = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		for (int i = 0; i < numGridCells; i++)
		{
			mpGrid->setValueAtIndex(i, CLEAR_VALUE);
		}
	}

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0.0f, 0.0f, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	InputSystem* pInputSystem = getInputSystem();
	pInputSystem->update(mLoopTargetTime);

	if (pInputSystem->isMouseButtonPressed(InputSystem::LEFT))
	{
		Vector2D pos = pInputSystem->getCurrentMousePos();
		mpGrid->setValueAtPixelXY((int)pos.getX(), (int)pos.getY(), BLOCKING_VALUE);
		mpGridVisualizer->setModified();
	}
	else if (pInputSystem->isMouseButtonPressed(InputSystem::RIGHT))
	{
		Vector2D pos = pInputSystem->getCurrentMousePos();
		mpGrid->setValueAtPixelXY((int)pos.getX(), (int)pos.getY(), CLEAR_VALUE);
		mpGridVisualizer->setModified();
	}

	if (pInputSystem->isKeyPressed(InputSystem::ESCAPE_KEY))
	{
		markForExit();
	}
	else if (pInputSystem->isKeyPressed(InputSystem::S_KEY))//save the grid
	{
		ofstream theStream(gFileName);
		saveGrid(theStream);
		theStream.close();
		cout << "Grid saved!\n";
		Sleep(1000);//very bogus
	}
	else if (pInputSystem->isKeyPressed(InputSystem::L_KEY))//load the grid
	{
		ifstream theStream(gFileName);
		loadGrid(theStream);
		theStream.close();
		getGridVisualizer()->setModified();
		cout << "Grid loaded!\n";
		Sleep(1000);//very bogus
	}

	//get back buffer
	GraphicsBuffer* pBackBuffer = getGraphicsSystem()->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw(*pBackBuffer);

	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
	mpGrid->load(theStream);
}
