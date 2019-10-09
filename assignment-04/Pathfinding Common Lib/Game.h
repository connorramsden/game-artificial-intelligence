#pragma once

/* Game - base class for actual application class

	Dean Lawson
	Champlain College
	2011
*/
#include <Trackable.h>
#include <Timer.h>
#include <Defines.h>
#include <System.h>

class MemoryTracker;
class PerformanceTracker;
class System;
class GraphicsSystem;
class InputSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class FontManager;
class Game;

extern PerformanceTracker* gpPerformanceTracker;
extern Game* gpGame;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType COUR_20_FONT_ID = 0;


class Game:public Trackable
{
public:
	Game();
	virtual ~Game();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpSystem->getGraphicsSystem(); };
	inline System* getSystem() const { return mpSystem; };
	inline InputSystem* getInputSystem() const { return mpSystem->getInputSystem(); };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline FontManager* getFontManager() const { return mpFontManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline void markForExit() { mShouldExit = true; };

protected:
	System* mpSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	FontManager* mpFontManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	float mLoopTargetTime;
	bool mShouldExit;

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float mapRotationToRange( float rotation, float low, float high );

