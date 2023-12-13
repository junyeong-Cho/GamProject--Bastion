

#include "../Engine/GameObjectManager.h"

#include "Monster.h"
#include "Wave.h"
#include "Map.h"
#include "Gold.h"
#include "Tower.h"


void Wave::SetWave()
{
	// Get wave info from the Map
	wave_info = Map::GetInstance().GetWaveInfo();

	// Set total wave num
	total_wave_num = static_cast<int>(wave_info.size());
	current_wave = 0;
}

void Wave::Start() 
{ 
	// For debug
	if (current_wave >= total_wave_num)
	{
		Engine::GetLogger().LogDebug("Stop!!!!");
		return;
	}

	// Player cannot start the game if there is remaining monsters or if the wave is in progress
	if (Monster::GetRemainMonster() > 0 || wave_state != NotInProgress)
		return;

	// Set wave state to InProgress
	wave_state = Wave_State::InProgress; 
	wave_of_wave_ended = false;
	current_time = 0;

	// Get total wave of wave from the wave_info
	total_wave_of_wave = static_cast<int>(wave_info[current_wave].size());
	current_wave_of_wave = -1;

	wave_time = 0;

	Engine::GetLogger().LogDebug("Total wave of wave: " + std::to_string(total_wave_of_wave));
	Engine::GetLogger().LogEvent("Wave " + std::to_string(current_wave + 1) + " starts!");
}

void Wave::Choice(int choice)
{
	// some mechanism

	//// 1
	//Player::EnableShotGun();
	//// 2
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->SlowAllMonsters();
	//// 3
	//Player::UpgradeAttackSpeed();
	//// 4
	//Player::UpgradeAttackDmg();
	//// 5
	//Engine::GetGameStateManager().GetGSComponent<Gold>()->Upgrade();
	//// 6
	//Tower::Enable_Supply_Ammo();
	//// 7
	//Player::EnableRecover();
	//// 8
	//Player::EnableGodMode();
	//// 9
	//Player::UpgradeAttackDmg();
	//Player::UpgradeAttackSpeed();


	switch (choice)
	{
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	default:
		break;
	}


	Engine::GetGameStateManager().GetGSComponent<Gold>()->Interest();
	if (Tower::Supply_Enabled())
	{
		Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->SupplyAllTower();
	}
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetPlayer()->Recover();
	wave_state = Wave_State::NotInProgress;
}

void Wave::Update(double dt)
{
	switch (wave_state)
	{
	case Wave_State::NotInProgress:


		break;

	case Wave_State::InProgress:

		// Wave update
		if (wave_of_wave_ended)
		{
			if (Monster::GetRemainMonster() == 0)
			{
				wave_state = Wave_State::Term;
				term_time_count = 0;
				++current_wave;

				// Win state
				if (current_wave >= total_wave_num && Monster::GetRemainMonster() == 0)
				{
					Engine::GetLogger().LogEvent("Win!");
					Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Win));
					return;
				}
			}
			return;
		}


		// Update the time
		current_time += dt;
		monster_produce_time_count += dt;

		// Monster Wave
		if (current_time > wave_time)
		{
			++current_wave_of_wave;
			if (current_wave_of_wave >= total_wave_of_wave)
			{
				Engine::GetLogger().LogEvent("Wave of wave end.");
				wave_of_wave_ended = true;
				return;
			}

			// Reset the current time and get information of wave from the wave_info
			current_time = 0;
			std::tie(wave_time, monster_name, monster_num) = wave_info[current_wave][current_wave_of_wave];

			// Update the time_offset
			time_offset = wave_time / monster_num;
		}

		// Produce monster
		if (monster_produce_time_count > time_offset)
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
			else if (monster_name == "WEAK")
			{
				new Weak_Monster;
			}
			else if (monster_name == "MOMM")
			{
				new Mother_Monster;
			}
			else if (monster_name == "STLT")
			{
				new Stealth_Monster;
			}
			else if (monster_name == "HEAL")
			{
				new Heal_Monster;
			}
			else if (monster_name == "BOMB")
			{
				new Bomb_Monster;
			}
			else if (monster_name == "NONE")
			{

			}
		}


		break;

	case Wave_State::Term:
		term_time_count += dt;
		if (term_time_count >= term_time)
			wave_state = Wave_State::Upgrade;

		break;

	case Wave_State::Upgrade:

		

		break;
	}

	
}
