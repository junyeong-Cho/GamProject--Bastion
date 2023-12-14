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

#include <limits>

#include "GameObjectManager.h"
#include "GameObject.h"

#include "../Game/GameObjectTypes.h"
#include "../Game/Monster.h"
#include "../Game/Tower.h"
#include "../Game/Button.h"
#include "../Game/BuildMode.h"
#include "../Game/Gold.h"


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

	Player::Unload();

	Basic_Monster::Restore();
	Slow_Monster::Restore();
	Fast_Monster::Restore();
	Weak_Monster::Restore();
	Mother_Monster::Restore();
	Stealth_Monster::Restore();
	Heal_Monster::Restore();

	Engine::GetGameStateManager().GetGSComponent<Gold>()->Restore();
	Tower::Unable_Supply_Ammo();

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
		//Engine::GetLogger().LogEvent(object->TypeName());
		
		object->Draw(camera_matrix);
	}
}

void GAM200::GameObjectManager::CollisionTest()
{

	for (GameObject* object_1 : objects)
	{
		//Engine::GetLogger().LogEvent("First loop: checking " + object_1->TypeName());
		for (GameObject* object_2 : objects)
		{
			//Engine::GetLogger().LogEvent("Second loop: checking " + object_2->TypeName());
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


Monster* GAM200::GameObjectManager::GetClosestMonster(GAM200::GameObject* obj) {
	double optimal_distance = std::numeric_limits<double>::max();
	Monster* closest_object = nullptr;

	for (GameObject* object : objects) {
		if (object != obj && object->Destroyed() != true) {
			if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
				static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End)) 
			{
				double distance = obj->GetSquareDistance(object);
				if (distance < optimal_distance) {
					optimal_distance = distance;
					closest_object = static_cast<Monster*>(object);
				}
			}
		}
	}

	return closest_object;
}


std::vector<Monster*> GAM200::GameObjectManager::GetMonstersInRange(GAM200::GameObject* obj, double range)
{
	std::vector<Monster*> monsters;
	
	for (GameObject* object : objects) {
		if (object != obj) {
			if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Monster) &&
				static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Monster_End) &&
				!(object->Destroyed()) &&
				object->Type() != GameObjectTypes::Heal_Monster)
			{
				double distance = obj->GetSquareDistance(object);
				Monster* monster = static_cast<Monster*>(object);
				if (distance <= range * range)
					monsters.emplace_back(monster);

			}
		}
	}

	return monsters;
}


Player* GAM200::GameObjectManager::GetPlayer()
{
	for (GameObject* object : objects) {
		if (object->Type() == GameObjectTypes::Player)
		{
			Player* player = static_cast<Player*>(object);
			return player;
		}
	}
	return nullptr;
}


void GAM200::GameObjectManager::RecoverAllTower()
{
	for (GameObject* object : objects)
	{
		if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Tower) &&
			static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Tower_End))
		{
			Tower* tower = static_cast<Tower*>(object);
			tower->Recover();
		}
	}
}



void GAM200::GameObjectManager::SupplyAllTower()
{
	for (GameObject* object : objects)
	{
		if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Tower) &&
			static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Tower_End))
		{
			Tower* tower = static_cast<Tower*>(object);
			tower->supply_ammo();
		}
	}
}


void GAM200::GameObjectManager::SlowAllMonsters()
{
	Basic_Monster::Slow();
	Slow_Monster::Slow();
	Fast_Monster::Slow();
	Weak_Monster::Slow();
	Mother_Monster::Slow();
	Stealth_Monster::Slow();
	Heal_Monster::Slow();
}



void GAM200::GameObjectManager::BombToTower(Monster* monster, double range)
{
	Math::vec2 monster_position = monster->GetPosition();
	for (GameObject* object : objects)
	{
		if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Tower) &&
			static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Tower_End))
		{
			Tower* tower = static_cast<Tower*>(object);
			Math::vec2 tower_positoin = Math::vec2{ tower->GetPosition().x + 40, tower->GetPosition().y + 40 };

			double square_distance = (tower_positoin.x - monster_position.x) * (tower_positoin.y - monster_position.y);
			if (square_distance < range * range)
			{
				Engine::GetLogger().LogDebug("nice");
				tower->Damaged(3);
			}
		}
	}
}

void GAM200::GameObjectManager::Click_Handle()
{


	for (GameObject* object : objects)
	{
		if (object->Type() == GameObjectTypes::Button)
		{
			Button* button = static_cast<Button*>(object);

			if (button->IsClicked())
			{
				Engine::GetLogger().LogDebug("Button clicked");
				return;
			}
		}

	}

	for (GameObject* object : objects)
	{
		if (static_cast<int>(object->Type()) >= static_cast<int>(GameObjectTypes::Tower) &&
			static_cast<int>(object->Type()) <= static_cast<int>(GameObjectTypes::Tower_End))
		{
			Tower* tower = static_cast<Tower*>(object);

			if (tower->IsClicked())
			{
				Engine::GetLogger().LogDebug("Tower clicked");
				return;
			}
		}

	}


	if (Engine::GetGameStateManager().GetGSComponent<BuildMode>()->Click())
		return;

	this->GetPlayer()->Attack();
}