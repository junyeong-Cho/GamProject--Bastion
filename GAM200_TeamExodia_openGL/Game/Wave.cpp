#include "Wave.h"
#include "Map.h"

#include "../Engine/GameObjectManager.h"

#include "Monster.h"


void Wave::SetWave()
{
	wave_info = Map::GetInstance().GetWaveInfo();

	total_wave_num = static_cast<int>(wave_info.size());
	current_wave = 0;
}

void Wave::Start() 
{ 
	if (current_wave >= total_wave_num)
	{
		Engine::GetLogger().LogDebug("Stop!!!!");
		return;
	}

	if (Monster::GetRemainMonster() > 0)
		return;

	wave_state = Wave_State::InProgress; 
	current_time = 0;

	total_wave_of_wave = static_cast<int>(wave_info[current_wave].size());
	Engine::GetLogger().LogDebug("Total wave of wave: " + std::to_string(total_wave_of_wave));
	current_wave_of_wave = -1;

	wave_time = 0;

	Engine::GetLogger().LogEvent("Wave " + std::to_string(current_wave + 1) + " starts!");
}

void Wave::Update(double dt)
{

	if (current_wave >= total_wave_num && Monster::GetRemainMonster() == 0)
	{
		Engine::GetLogger().LogEvent("Win!");
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Win));
		return;
	}


	if (wave_state == Wave::NotInProgress)
		return;


	current_time += dt;
	monster_produce_time_count += dt;

	if (current_time >= wave_time)
	{
		++current_wave_of_wave;
		if (current_wave_of_wave >= total_wave_of_wave)
		{
			Engine::GetLogger().LogEvent("Wave end.");
			wave_state = Wave_State::NotInProgress;
			++current_wave;
			return;
		}

		current_time = 0;
		wave_time = std::get<0>(wave_info[current_wave][current_wave_of_wave]);
		monster_name = std::get<1>(wave_info[current_wave][current_wave_of_wave]);
		monster_num = std::get<2>(wave_info[current_wave][current_wave_of_wave]);

		time_offset = wave_time / monster_num;
	}

	if (monster_produce_time_count >= time_offset)
	{
		monster_produce_time_count = 0;

		if (monster_name == "BASIC")
		{
			new Basic_Monster;
		}
		else if (monster_name == "FAST")
		{
			new Fast_Monster;
		}
		else if (monster_name == "SLOW")
		{
			new Slow_Monster;
		}
		else if (monster_name == "NONE")
		{

		}
	}


}

/*
int wave_time = get<0>(wave_info[current_wave - 1][wave_index]);
std::string monster_name = get<1>(wave_info[current_wave - 1][wave_index]);
int monster_num = get<2>(wave_info[current_wave - 1][wave_index]);
*/