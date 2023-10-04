/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameStateManager.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    September 30, 2023
*/

#pragma once
#include "Gamestate.h"
#include <vector>

namespace GAM200
{
	class GameStateManager
	{
	public:
		GameStateManager();

		void Update(double dt);

		void AddGameState(GameState& gamestate);
		void SetNextGameState(int index);
		void ClearNextGameState();
		void ReloadGameState();
		bool HasGameEnded() { return status == Status::EXIT; }

		SDL_Event GetCurrentEvent() { }

		template<typename T>
		T* GetGSComponent()
		{
			return current_gamestate->GetGSComponent<T>();
		}

	private:
		enum class Status
		{
			STARTING,
			LOADING,
			UPDATING,
			UNLOADING,
			STOPPING,
			EXIT
		};

		Status status = Status::STARTING;

		std::vector<GameState*> gamestates;

		GameState* current_gamestate = nullptr;
		GameState* next_gamestate = nullptr;
	};
}