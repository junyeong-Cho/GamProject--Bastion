#include "Score.h"

void Score::Add(int value)
{
	scoreValue += value;
}

int Score::Value() const
{
	return scoreValue;
}
