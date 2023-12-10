/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameStateManager.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    September 30, 2023
*/



#include "Engine.h"

#include "GameStateManager.h"
#include "ImGuiHelper.h"
#include "GameObjectManager.h"
//#include "GameObjectManager.h"


GAM200::GameStateManager::GameStateManager() { }

void GAM200::GameStateManager::AddGameState(GameState& gamestate)
{
	gamestates.push_back(&gamestate);
}



//gamestate�� ���Ϳ��ٰ� �����س���, �װ��� index ���� ������ ����ؼ� �ٲٱ� ������
//main�� state�� �ִ� ������ �߿���!
void GAM200::GameStateManager::SetNextGameState(int index)
{
	next_gamestate = gamestates[index];
}


void GAM200::GameStateManager::ReloadGameState()
{
	status = Status::UNLOADING;
}

void GAM200::GameStateManager::ClearNextGameState()
{
	next_gamestate = nullptr;
}

void GAM200::GameStateManager::Update(double dt)
{
	switch (status)
	{
	case GAM200::GameStateManager::Status::STARTING:

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


	case GAM200::GameStateManager::Status::LOADING:

		current_gamestate = next_gamestate;

		Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
		current_gamestate->Load();
		Engine::GetLogger().LogEvent("Load Complete");

		status = Status::UPDATING;

		break;

	case GAM200::GameStateManager::Status::UPDATING:

		if (current_gamestate != next_gamestate)
		{
			status = Status::UNLOADING;
		}
		else
		{
			SDL_Event event{ 0 };

			while (SDL_PollEvent(&event) != 0)
			{
				ImGuiHelper::FeedEvent(event);
				//Engine::GetMouse().HandleEvent(event);

				Engine::GetInput().HandleEvent(event);
				//Engine::GetWindow().Update();

				if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE))
				{
					Engine::GetGameStateManager().ClearNextGameState();
				}
			}

			Engine::GetLogger().LogVerbose("Update" + current_gamestate->GetName());
			current_gamestate->Update(dt);


			GameObjectManager* game_object_manager = GetGSComponent<GameObjectManager>();

			if (game_object_manager != nullptr)
			{
				game_object_manager->CollisionTest();
			}


			current_gamestate->Draw();


			//�̰� �� ��?;;
			ImGuiHelper::Begin();

			current_gamestate->ImguiDraw();


			ImGuiHelper::End(Engine::Instance().GetWindow().GetSDLWindow(), Engine::Instance().GetWindow().GetGLContext());
			
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

