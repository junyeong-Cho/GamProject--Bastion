/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameSpeed.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Hyeonjoon Nam
Created:    December 15, 2023
Updated:    December 15, 2023
*/

#include "GameSpeed.h"

void GameSpeed::NextSpeed()
{
	game_speed += 1;
	if (game_speed > max_speed)
		game_speed = 1;
}

int GameSpeed::Value() const
{
	return game_speed;
}

int GameSpeed::GetMax() const
{
	return max_speed;
}
