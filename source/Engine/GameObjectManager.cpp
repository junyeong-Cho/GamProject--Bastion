/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#include <limits>
#include <cmath>
#include <float.h>

#include "GameObjectManager.h"
#include "GameObject.h"

#include "../Game/GameObjectTypes.h"
#include "../Game/Objects/Units/Unit.h"
#include "../Game/Objects/Monsters/Monster.h"

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
		object->Draw(camera_matrix);
	}
}

void GAM200::GameObjectManager::DrawParticle(Math::TransformationMatrix camera_matrix)
{
	for (GameObject* object : objects)
	{
		if (object->Type() != GameObjectTypes::Particle)
			continue;
		object->Draw(camera_matrix);
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
					object_1->ResolveCollision(object_2);
				}
			}
		}
	}
}

void GAM200::GameObjectManager::MergeTest()
{
	// Check only when the mouse is released
	if (!Engine::GetInput().MouseJustReleased(GAM200::Input::MouseButtons::LEFT))
		return;

	if (current_unit == nullptr)
		return;

	for (GameObject* target : objects)
	{
		if (target->Type() == GameObjectTypes::Monster)
			continue;

		if (current_unit == target)
			continue;

		if (current_unit->IsMergingWith(target))
		{
			if (current_unit->CanMergeWith(target->Type()))
			{
				current_unit->ResolveMerge(target);
				current_unit = nullptr;
				return;
			}
			else
			{
				current_unit->SetPosition(current_unit->GetPreviousPosition());

				return;
			}
		}
	}
}

Unit* GAM200::GameObjectManager::GetClosestUnit(Unit* unit)
{
	double current_distance = DBL_MAX;
	Unit* closest_unit = nullptr;

	for (GameObject* object : objects)
	{
		if (object->Type() == GameObjectTypes::Monster)
			continue;
		else
		{
			Math::vec2 unit_position = unit->GetPosition();
			Math::vec2 target_position = object->GetPosition();
			double squared_distance = pow(unit_position.x - target_position.x, 2) + pow(unit_position.y - target_position.y, 2);

			if (pow(unit->GetRadius(), 2) < squared_distance)
				continue;

			if (current_distance < squared_distance)
			{
				closest_unit = static_cast<Unit*>(object);
				current_distance = squared_distance;
			}
		}
	}

	return closest_unit;
}

Unit* GAM200::GameObjectManager::GetClosestUnit(Math::vec2 position)
{
	double current_distance = DBL_MAX;
	Unit* closest_unit = nullptr;

	for (GameObject* object : objects)
	{
		if (object->Type() == GameObjectTypes::Monster)
		{
			continue;
		}
		else
		{
			Math::vec2 target_position = object->GetPosition();
			double squared_distance = pow(position.x - target_position.x, 2) + pow(position.y - target_position.y, 2);

			if (squared_distance < current_distance)
			{
				closest_unit = static_cast<Unit*>(object);
				current_distance = squared_distance;
			}
		}
	}
	current_unit = closest_unit;

	return closest_unit;
}

void GAM200::GameObjectManager::StunUnits(Math::vec2 position, double range)
{
	for (GameObject* object : objects)
	{
        if (object->Type() < GameObjectTypes::Unit || object->Type() > GameObjectTypes::UnitEnd)
			continue;
		else
        {
            Math::vec2 unit_position    = object->GetPosition();
            double     squared_distance = pow((unit_position.x - position.x), 2) + pow((unit_position.y - position.y), 2);

			if (squared_distance < pow(range, 2))
			{
                Unit* unit = dynamic_cast<Unit*>(object);
                unit->stunned = true;
			}
		}
	}
}

bool GAM200::GameObjectManager::IsMonserNear(Unit* unit)
{
	for (GameObject* object : objects)
	{
		if (object->Type() != GameObjectTypes::Monster)
			continue;
		else
		{
			Math::vec2 unit_position = unit->GetPosition();
			Math::vec2 target_position = object->GetPosition();
			double squared_distance = pow((unit_position.x - target_position.x), 2) + pow((unit_position.y - target_position.y), 2);

			if (pow(unit->GetRange(), 2) > squared_distance)
				return true;
		}
	}
	return false;
}

Monster* GAM200::GameObjectManager::GetClosestMonster(Unit* unit)
{
	double current_distance = DBL_MAX;
	Monster* closest_monster = nullptr;

	for (GameObject* object : objects)
	{
		if (object->Type() != GameObjectTypes::Monster)
			continue;
		else
		{
			Math::vec2 unit_position = unit->GetPosition();
			Math::vec2 target_position = object->GetPosition();
			double squared_distance = pow(unit_position.x - target_position.x, 2) + pow(unit_position.y - target_position.y, 2);

			if (pow(unit->GetRadius(), 2) < squared_distance)
				continue;

			if (current_distance < squared_distance)
			{
				closest_monster = static_cast<Monster*>(object);
				current_distance = squared_distance;
			}
		}
	}

	return closest_monster;
}

Monster* GAM200::GameObjectManager::GetClosestMonster(Math::vec2 position)
{
	double current_distance = DBL_MAX;
	Monster* closest_monster = nullptr;

	for (GameObject* object : objects)
	{
		if (object->Type() != GameObjectTypes::Monster)
		{
			continue;
		}
		else
		{
			Math::vec2 target_position = object->GetPosition();
			double squared_distance = pow(position.x - target_position.x, 2) + pow(position.y - target_position.y, 2);

			if (squared_distance < current_distance)
			{
				closest_monster = static_cast<Monster*>(object);
				current_distance = squared_distance;
			}
		}
	}

	return closest_monster;
}


double GAM200::GameObjectManager::WideDamage(Math::vec2 position, double radius, double damage)
{
	double totalDamage = 0;

	for (GameObject* object : objects)
	{
		if (object->Type() != GameObjectTypes::Monster)
			continue;

		double squaredDistance = (position - object->GetPosition()).GetSquaredLength();
		if (squaredDistance <= pow(radius, 2))
		{
			Monster* monster = static_cast<Monster*>(object);
			monster->TakeDamage(damage);
			totalDamage += damage;
		}
	}

	return totalDamage;
}

void GAM200::GameObjectManager::DeleteAllMonster()
{
    std::vector<GameObject*> monsters_to_destroy;

    for (GameObject* object : objects)
    {
        if (object->Type() == GameObjectTypes::Monster)
        {
            monsters_to_destroy.push_back(object);
        }
    }

    for (GameObject* monster : monsters_to_destroy)
    {
        auto it = std::find(objects.begin(), objects.end(), monster);
        if (it != objects.end())
        {
            objects.erase(it);
        }
        delete monster;
    }
}

void GAM200::GameObjectManager::ApplyDebuff(Math::vec2 position, double range, double debuffFactor)
{
    for (GameObject* object : objects)
    {
        if (object->Type() > GameObjectTypes::Unit && object->Type() < GameObjectTypes::UnitEnd)
        {
            Unit*  unit            = dynamic_cast<Unit*>(object);

			double squared_distance = (unit->GetPosition().x - position.x) * (unit->GetPosition().x - position.x) + (unit->GetPosition().y - position.y) * (unit->GetPosition().y - position.y); 

			if (squared_distance <= pow(range, 2))
				unit->BuffDmg(debuffFactor);
        }
    }
}