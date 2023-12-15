/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Life.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

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
