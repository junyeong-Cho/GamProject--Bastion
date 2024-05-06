/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ComponentManager.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    September 30, 2023
Updated:    September 30, 2023
*/

#pragma once

#include <vector>
#include <algorithm>

#include "Engine/Component.h"

namespace GAM200
{
	class ComponentManager
	{
	public:
		~ComponentManager() { }

		void UpdateAll(double dt)
		{
			for (Component* component : components)
			{
				component->Update(dt);
			}
		}

		//push_back certen component to the components vector
		void AddComponent(Component* component)
		{
			components.push_back(component);
		}


		template<typename T>
		T* GetComponent()
		{
			for (Component* component : components)
			{

				T* ptr = dynamic_cast<T*>(component);

				if (ptr != nullptr)
				{
					return ptr;
				}

			}

			return nullptr;
		}


		template<typename T>
		void RemoveComponent()
		{
			auto it = std::find_if
			(
				components.begin(), components.end(), [](Component* element)
			{
				return (dynamic_cast<T*>(element) != nullptr);
			}
			);

			delete* it;
			components.erase(it);
		}


		void Clear()
		{
			for (Component* component : components)
			{
				delete component;
			}

			components.clear();
		}


	private:
		std::vector<Component*> components;

	};
}

