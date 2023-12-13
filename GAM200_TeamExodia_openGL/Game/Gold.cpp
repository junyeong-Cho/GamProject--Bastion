#include "Gold.h"

void Gold::Add(int value)
{
	goldValue += value;
}

void Gold::Subtract(int value)
{
	goldValue -= value;
}

int Gold::Value() const
{
	return goldValue;
}

void Gold::Interest()
{
	goldValue += goldValue / 10;
}