#include "GameMessage.h"

#include <string>
using std::string;

class WeightMessage : public GameMessage
{
public:
	WeightMessage(string weightToChange);

	void process();
private:
	string mWeight;
};
