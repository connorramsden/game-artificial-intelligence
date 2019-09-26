#pragma once
#include "GameMessage.h"
class ExitMessage :	public GameMessage
{
public:
	ExitMessage();
	~ExitMessage();

	void process();
};
