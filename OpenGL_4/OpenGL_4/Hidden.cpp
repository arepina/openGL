#include "Hidden.h"
#include <ctime>
#include <random>

Hidden::Hidden(int housesNum)
{
	srand(time(0));
	whereHidden = rand() % housesNum + 1;
}

int Hidden::getHidden()
{
	return whereHidden;
}
