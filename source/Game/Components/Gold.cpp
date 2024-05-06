/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Gold.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

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
	goldValue += static_cast<int>(goldValue * interest_rate);
}

void Gold::Upgrade()
{
	interest_rate += 0.2;
}

void Gold::Restore()
{
	//double interest_rate = 0.2;
}