/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Normalization.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October    4, 2023
Updated:    October    5, 2023
*/

#pragma once

#include <iostream>


#include "Engine.h"


namespace Math
{
	float NormalizeX(int x, int windowWidth);

	float NormalizeY(int y, int windowHeight);
}