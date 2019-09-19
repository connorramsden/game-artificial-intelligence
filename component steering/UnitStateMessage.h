#pragma once

#include <string>
using std::string;

#include "GameMessage.h"
#include "Vector2D.h"
#include "Steering.h"

class Vector2D;
enum Steering::SteeringType;

class UnitStateMessage : public GameMessage
{
public:
	UnitStateMessage(string destroyOrCreate, Steering::SteeringType unitBehaviour = Steering::SteeringType::SEEK);
	~UnitStateMessage();

	void process();

private:
	string mDestroyOrCreate;
	Steering::SteeringType mBehaviour;
};
