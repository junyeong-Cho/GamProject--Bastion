#include "Life.h"

void Life::Add(int value)
{
	lifeValue += value;
}

void Life::Subtract(int value)
{
	lifeValue -= value;
}

int Life::Value() const
{
	return lifeValue;
}
