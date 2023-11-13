#include "GameSpeed.h"

void GameSpeed::NextSpeed()
{
	game_speed += 1;
	if (game_speed > max_speed)
		game_speed = 0;
}

int GameSpeed::Value() const
{
	return game_speed;
}

int GameSpeed::GetMax() const
{
	return max_speed;
}
