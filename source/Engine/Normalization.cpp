/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Normalization.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October    4, 2023
Updated:    October    10, 2023
*/

#include "Normalization.h"

float Math::NormalizeX(double x, int windowWidth)
{
	double normalizeX = (x / (windowWidth / 2)) - 1.0f;

	switch (Engine::GetWindow().GetOriginPosition())
	{
		// Flip the X-axis for right-oriented origins
	case OriginPosition::RIGHT_DOWN:
	case OriginPosition::RIGHT_UP:

		normalizeX = -normalizeX;

		break;

	default:

		break;
	}

	return static_cast<float>(normalizeX);
}


float Math::NormalizeY(double y, int windowHeight)
{
	double normalizeY = (y / (windowHeight / 2)) - 1.0f;

	switch (Engine::GetWindow().GetOriginPosition())
	{
		// Flip the Y-axis for bottom-oriented origins
	case OriginPosition::LEFT_UP:
	case OriginPosition::RIGHT_UP:

		normalizeY = -normalizeY;

		break;

	default:

		break;
	}

	return static_cast<float>(normalizeY);
}
