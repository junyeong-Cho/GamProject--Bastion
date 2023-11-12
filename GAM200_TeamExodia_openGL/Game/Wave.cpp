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
		Engine::GetLogger().LogDebug("스탑 새기야");
		return;
	}

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
	if (Engine::GetInput().KeyJustReleased(GAM200::Input::Keys::Space) && wave_state == Wave::NotInProgress)
	{
		Start();
	}


	if (current_wave >= total_wave_num)
		return;
	if (wave_state == Wave_State::NotInProgress)
	{
		//Engine::GetLogger().LogDebug("It's not in progress.");
		return;
	}

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
			Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Basic_Monster());
		}
		else if (monster_name == "FAST")
		{
			Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Fast_Monster());
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