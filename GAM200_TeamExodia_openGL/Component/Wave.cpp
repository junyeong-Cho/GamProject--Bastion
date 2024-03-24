

#include "Wave.h"
#include "Gold.h"

#include "../Engine/GameObjectManager.h"

#include "../Game/States.h"
#include "../Game/Monster.h"

#include <iostream>
#include <fstream>
#include <string>

void Wave::SetWave(std::string file_name)
{
	std::ifstream file(file_name);

	if (file.is_open())
	{
		// The number of total waves
		file >> total_wave;
		wave_info.clear();
		//wave_info.resize(total_wave);

		double rest_time;
		double wave_time;
		std::string type;
		int monster_num;

		for (int i = 0; i < total_wave; ++i)
		{
			file >> rest_time;
			file >> wave_time;
			file >> type;
			file >> monster_num;

			wave_info.emplace_back(std::make_tuple(rest_time, wave_time, type, monster_num));
		}
		file.close();
	}
}

void Wave::Skip()
{
	current_time = rest_time;
}

void Wave::Update(double dt)
{
	current_time += dt;

	switch (wave_state)
	{
	case WaveState::Battle:
		// Wave ended
		if (current_time > wave_time)
		{
			// Reset time
			current_time = 0.0;

			// Change the state
			wave_state = Rest;

			return;
		}

		monster_spawn_time_count += dt;
		if (monster_spawn_time_count > monster_spawn_time_offset)
		{
			monster_spawn_time_count = 0;
			// TODO
			/*if (monster_name == "SOMETHING")
			{
				new Something();
			}
			else (monster_name == "ANOTHER")
			{
				new Another();
			}*/

			new TestMonster();
		}


		break;

	case WaveState::Rest:
		// Rest ended
		if (current_time > rest_time)
		{
			// Reset time
			current_time = 0.0;


			// Get informations from the vector
			++current_wave;
			if (current_wave >= total_wave)
			{
				wave_state = WaveState::End;
				return;
			}

			std::tie(rest_time, wave_time, monster_name, monster_num) = wave_info[current_wave];


			Engine::GetLogger().LogDebug("Current Time: " + std::to_string(current_time));
			Engine::GetLogger().LogDebug("Rest Time: " + std::to_string(rest_time));
			Engine::GetLogger().LogDebug("Current Wave: " + std::to_string(current_wave) + '\n');

			// Calc the values
			monster_spawn_time_offset = wave_time / monster_num;

			// Change the state
			wave_state = Battle;

			return;
		}

		break;

	case End:
		Engine::GetLogger().LogDebug("It's end!");
		break;

	}
}