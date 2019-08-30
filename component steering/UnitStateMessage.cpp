#include "Game.h"
#include "GameMessageManager.h"
#include "UnitStateMessage.h"
#include "UnitManager.h"
#include "SpriteManager.h"

UnitStateMessage::UnitStateMessage(string destroyOrCreate, bool behaviorToProcess)
	:GameMessage(UNIT_STATE_MESSAGE)
	, mBehaviour(behaviorToProcess)
	, mDestroyOrCreate(destroyOrCreate)
{

}

UnitStateMessage::~UnitStateMessage()
{}

void UnitStateMessage::process()
{
	if (mDestroyOrCreate == "create")
	{
		Unit* pUnit = gpGame->getUnitManager()->createRandomUnit(*gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), mBehaviour);
	}
	else
	{
		gpGame->getUnitManager()->deleteRandomUnit();
	}
}
