/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  ComponentManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8, 2023
Updated:    September 26, 2023
*/

#pragma once

#include <vector>
#include <algorithm>

#include "Component.h"

namespace CS230
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

				//T는 특정타입이 없기 때문에, component를 T*로 바꿔주는 것이다.
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

