#include "WeightMessage.h"
#include "Game.h"
#include "DataRepository.h"
#include "DataLoader.h"

WeightMessage::WeightMessage(string weightToChange)
	:GameMessage(WEIGHT_MESSAGE)
{
	mWeight = weightToChange;
}

void WeightMessage::process()
{
	DataRepository* pRepository = gpGame->getDataRepository();

	if (mWeight == "cu")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::COHESION_WEIGHT).getFloatVal();
		if (newWeight < 1.0f)
			newWeight += 0.1f;
		else
			newWeight = 1.0f;
		pRepository->addEntry(DataKeyEnum::COHESION_WEIGHT, newWeight);
	}
	else if (mWeight == "cd")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::COHESION_WEIGHT).getFloatVal();
		if (newWeight > 0.0f)
			newWeight -= 0.1f;
		else
			newWeight = 0.0f;

		pRepository->addEntry(DataKeyEnum::COHESION_WEIGHT, newWeight);
	}
	else if (mWeight == "gu")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::ALIGN_WEIGHT).getFloatVal();
		if (newWeight < 1.0f)
			newWeight += 0.1f;
		else
			newWeight = 1.0f;
		pRepository->addEntry(DataKeyEnum::ALIGN_WEIGHT, newWeight);
	}
	else if (mWeight == "gd")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::ALIGN_WEIGHT).getFloatVal();
		if (newWeight > 0.0f)
			newWeight -= 0.1f;
		else
			newWeight = 0.0f;
		
		pRepository->addEntry(DataKeyEnum::ALIGN_WEIGHT, newWeight);
	}
	else if (mWeight == "su")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::SEPARATION_WEIGHT).getFloatVal();
		if (newWeight < 1.0f)
			newWeight += 0.1f;
		else
			newWeight = 1.0f;
		pRepository->addEntry(DataKeyEnum::SEPARATION_WEIGHT, newWeight);
	}
	else if (mWeight == "sd")
	{
		float newWeight = pRepository->getEntry(DataKeyEnum::SEPARATION_WEIGHT).getFloatVal();
		if (newWeight > 0.0f)
			newWeight -= 0.1f;
		else
			newWeight = 0.0f;
		pRepository->addEntry(DataKeyEnum::SEPARATION_WEIGHT, newWeight);
	}
}
