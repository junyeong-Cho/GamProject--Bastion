

#include "Wave.h"
#include "Gold.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/Audio.h"

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

			if (monster_name == "MONSTER1")
			{
				new Monster_1();
			}
			else if (monster_name == "MONSTER2")
			{
				new Monster_2();
			}
			else if (monster_name == "MONSTER3")
			{
				new Monster_3();
			}
			else if (monster_name == "MONSTER4")
			{
				new Monster_4();
			}
			else if (monster_name == "MONSTER5")
			{
				new Monster_5();
			}
			else if (monster_name == "MONSTER6")
			{
				new Monster_6();
			}
			else if (monster_name == "MONSTER7")
			{
				new Monster_7();
			}
			else if (monster_name == "MONSTER8")
			{
				new Monster_8();
			}
			else if (monster_name == "MONSTER9")
			{
				new Monster_9();
			}
			else if (monster_name == "MONSTER10")
			{
				new Monster_10();
			}
			else if (monster_name == "MONSTER11")
			{
				new Monster_11();
			}
			else if (monster_name == "MONSTER12")
			{
				new Monster_12();
			}
			else if (monster_name == "MONSTER13")
			{
				new Monster_13();
			}
			else if (monster_name == "MONSTER14")
			{
				new Monster_14();
			}
			else if (monster_name == "MONSTER15")
			{
				new Monster_15();
			}
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
				--current_wave;
				return;
			}

			std::tie(rest_time, wave_time, monster_name, monster_num) = wave_info[current_wave];

			// Calc the values
			monster_spawn_time_offset = wave_time / monster_num;

			// Change the state
			wave_state = Battle;

			//Sound
			GAM200::SoundEffect::Wave_Start().play();

			return;
		}

		break;

	case End:

		break;

	}
}