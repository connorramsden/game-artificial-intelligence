#include "Game.h"
#include "GameMessageManager.h"
#include "ExitMessage.h"
#include "UnitManager.h"

ExitMessage::ExitMessage()
	:GameMessage(EXIT_MESSAGE)
{}

ExitMessage::~ExitMessage()
{}

void ExitMessage::process()
{
	gpGame->mShouldExit = true;
}
