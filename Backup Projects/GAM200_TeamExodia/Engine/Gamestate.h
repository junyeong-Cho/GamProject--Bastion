/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameState.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#pragma once

#include <string>

#include "../Engine/ComponentManager.h"


namespace CS230
{
	class GameState
	{
	public:
		virtual void Load()			   = 0;
		virtual void Update(double dt) = 0;
		virtual void Unload()		   = 0;
		virtual void Draw()			   = 0;

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