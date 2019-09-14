#pragma once

#include <string>
using std::string;

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitStateMessage : public GameMessage
{
public:
	UnitStateMessage(string destroyOrCreate, bool behaviorToProcess = false);
	~UnitStateMessage();

	void process();

private:
	string mDestroyOrCreate;
	bool mBehaviour;
};
