/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#include "GameObjectManager.h"

void GAM200::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}

void GAM200::GameObjectManager::Unload()
{
	for (GameObject* object : objects)
	{
		delete object;
	}

	objects.clear();
}

void GAM200::GameObjectManager::UpdateAll(double dt)
{

	std::vector<GameObject*> destroy_objects;

	for (GameObject* object : objects)
	{
		object->Update(dt);

		if (object->Destroyed() == true)
		{
			destroy_objects.push_back(object);
		}
	}


	for (GameObject* object : destroy_objects)
	{
		// find the object in the 'objects' list
		auto it = std::find(objects.begin(), objects.end(), object);

		// if object found, remove it from the 'objects' list
		if (it != objects.end())
		{
			objects.erase(it);
		}

		// delete the object from memory
		delete object;
	}

}

void GAM200::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (GameObject* object : objects)
	{
		//object->Draw(camera_matrix);
	}
}

void GAM200::GameObjectManager::CollisionTest()
{

	for (GameObject* object_1 : objects)
	{
		for (GameObject* object_2 : objects)
		{
			if (object_1 != object_2 && (object_1->CanCollideWith(object_2->Type())))
			{
				if (object_1->IsCollidingWith(object_2))
				{
					//Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());

					object_1->ResolveCollision(object_2);
				}
			}
		}
	}
}