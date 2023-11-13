/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameStateManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/


#include "Engine.h"

#include "GameStateManager.h"
#include "GameObjectManager.h"


CS230::GameStateManager::GameStateManager() { }

void CS230::GameStateManager::AddGameState(GameState& gamestate)
{
	gamestates.push_back(&gamestate);
}



//gamestate를 백터에다가 저장해놨고, 그것을 index 값을 추적해 계속해서 바꾸기 때문에
//main의 state를 넣는 순서가 중요함!
void CS230::GameStateManager::SetNextGameState(int index)
{
	next_gamestate = gamestates[index];
}


void CS230::GameStateManager::ReloadGameState()
{
	status = Status::UNLOADING;
}

void CS230::GameStateManager::ClearNextGameState()
{
	next_gamestate = nullptr;
}

void CS230::GameStateManager::Update(double dt)
{
	switch (status)
	{
	case CS230::GameStateManager::Status::STARTING:

		if (gamestates.empty())
		{
			status = Status::STOPPING;
		}
		else
		{
			next_gamestate = gamestates[0];
			status = Status::LOADING;
		}

		break;


	case CS230::GameStateManager::Status::LOADING:
		
		current_gamestate = next_gamestate;

		Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
		current_gamestate->Load();
		Engine::GetLogger().LogEvent("Load Complete");

		status = Status::UPDATING;

		break;

	case CS230::GameStateManager::Status::UPDATING:

		if (current_gamestate != next_gamestate)
		{
			status = Status::UNLOADING;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update" + current_gamestate->GetName());
			current_gamestate->Update(dt);

			GameObjectManager* game_object_manager = GetGSComponent<GameObjectManager>();

			if (game_object_manager != nullptr)
			{
				game_object_manager->CollisionTest();
			}


			current_gamestate->Draw();
		}


		break;


	case Status::UNLOADING:

		Engine::GetLogger().LogEvent("Unload " + current_gamestate->GetName());

		current_gamestate->Unload();
		Engine::GetLogger().LogEvent("Unload Complete");

		Engine::GetTextureManager().Unload();

		if (next_gamestate == nullptr)
		{
			status = Status::STOPPING;
		}
		else
		{
			status = Status::LOADING;
		}

		break;
	case Status::STOPPING:
		status = Status::EXIT;

		break;
	case Status::EXIT:
		break;
	}
}

