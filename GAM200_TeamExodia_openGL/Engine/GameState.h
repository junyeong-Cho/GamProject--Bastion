/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameState.h
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#pragma once

#include <string>

#include "../Engine/ComponentManager.h"

#include <SDL2/SDL.h>


namespace GAM200
{
	class GameState
	{
	public:
		virtual void Load()			   = 0;
		virtual void Update(double dt) = 0;
		virtual void Unload()		   = 0;
		virtual void Draw()			   = 0;

		virtual void ImguiDraw()					= 0;
		virtual void HandleEvent( SDL_Event& event) = 0;

		virtual std::string GetName()  = 0;


		template<typename T>
		T* GetGSComponent()
		{
			return componentmanager.GetComponent<T>();
		}



	protected:
		void AddGSComponent(Component* component)
		{
			componentmanager.AddComponent(component);
		}

		void UpdateGSComponents(double dt)
		{
			componentmanager.UpdateAll(dt);
		}

		template<typename T>
		void RemoveGSComponent()
		{
			componentmanager.RemoveComponent<T>();
		}

		void ClearGSComponent()
		{
			componentmanager.Clear();
		}


	private:
		ComponentManager componentmanager;

	};




}