

#include <iostream>
#include <fstream>
#include <string>

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "States.h"
#include "Monster.h"
#include "Bullet.h"
#include "Map.h"

#include "Score.h"
#include "Gold.h"
#include "Life.h"



// Monster class
Monster::Monster(Math::vec2 position) : GameObject(position) {
	// Tile Size
	tile_size = Math::vec2(Engine::GetWindow().GetSize().x / Map::GetInstance().GetSize().y, Engine::GetWindow().GetSize().y / Map::GetInstance().GetSize().x);
	size_x = static_cast<int>(tile_size.x * 2 / 3);
	size_y = static_cast<int>(tile_size.y * 2 / 3);
	walking_speed = (tile_size.x * 1.5);

	// Settings
	SetVelocity({ 0, 0 });
	AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size_x, size_y} }, this));
	tile_index = 0;

	// State
	/*current_state = &state_walking;
	current_state->Enter(this);*/

	// Remaining monster count
	++remaining_monsters;
}
int Monster::GetRemainMonster() {
	return remaining_monsters;
}
void Monster::Update(double dt) {
	GameObject::Update(dt);

}
void Monster::Draw(Math::TransformationMatrix camera_matrix) {
	/*GAM200::DrawShape monster;

	monster.SetColor(fill_color.r, fill_color.g, fill_color.b, 1.0f);

	monster.DrawRectangle(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);*/
	e.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
}




// Constructors
Basic_Monster::Basic_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_max_life = max_life;
	real_damage = Basic_Monster::damage;
	real_speed_scale = Basic_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Basic_Monster::score;
	real_gold = Basic_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];


	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Fast_Monster::Fast_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_max_life = max_life;
	real_damage = Fast_Monster::damage;
	real_speed_scale = Fast_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Fast_Monster::score;
	real_gold = Fast_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Slow_Monster::Slow_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_max_life = max_life;
	real_damage = Slow_Monster::damage;
	real_speed_scale = Slow_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Slow_Monster::score;
	real_gold = Slow_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Mother_Monster::Mother_Monster(Math::vec2 position)
{
	life = max_life;
	real_max_life = max_life;
	real_damage = Mother_Monster::damage;
	real_speed_scale = Mother_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Mother_Monster::score;
	real_gold = Mother_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Weak_Monster::Weak_Monster(Math::vec2 position) : Monster(position)
{
	Engine::GetLogger().LogDebug("Weak monster constructor with basic constructor");
	life = max_life;
	real_max_life = max_life;
	real_damage = Weak_Monster::damage;
	real_speed_scale = Weak_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Weak_Monster::score;
	real_gold = Weak_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];


	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Weak_Monster::Weak_Monster(Mother_Monster* monster) : Monster(monster->GetPosition())
{
	Engine::GetLogger().LogDebug("Weak monster constructor with mother monster");
	life = max_life;
	real_max_life = max_life;
	real_damage = Weak_Monster::damage;
	real_speed_scale = Weak_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Weak_Monster::score;
	real_gold = Weak_Monster::gold;

	path = Astar::GetInstance().GetPath();
	tile_index = monster->tile_index;
	current_tile_position = monster->current_tile_position;
	next_tile_position = monster->next_tile_position;
	SetPosition(monster->GetPosition());

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Heal_Monster::Heal_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_max_life = max_life;
	real_damage = Heal_Monster::damage;
	real_speed_scale = Heal_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Heal_Monster::score;
	real_gold = Heal_Monster::gold;


	// Path finding
	path = Astar::GetInstance().GetPath();

	current_tile_position = path[tile_index++];

	// Set Direction, speed, position...
	Math::ivec2 direction = path[1] - path[0];
	if (direction.x == 1)
	{
		m_walking_direction = WalkingDirection::Right;
	}
	else if (direction.x == -1)
	{
		m_walking_direction = WalkingDirection::Left;
	}
	else if (direction.y == 1)
	{
		m_walking_direction = WalkingDirection::UP;
	}
	else if (direction.y == -1)
	{
		m_walking_direction = WalkingDirection::DOWN;
	}
	else
	{
		Engine::GetLogger().LogError("Monster Direction Error!");
	}

	next_tile_position = path[tile_index++];

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
Stealth_Monster::Stealth_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_max_life = max_life;
	real_damage = Stealth_Monster::damage;
	real_speed_scale = Stealth_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Stealth_Monster::score;
	real_gold = Stealth_Monster::gold;

	// Path finding
	path = Astar::GetInstance().GetPath();
	current_tile_position = path[tile_index++];

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}



// Update functions
void Basic_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Fast_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Slow_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Mother_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Weak_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Heal_Monster::Update(double dt)
{
	GameObject::Update(dt);

}
void Stealth_Monster::Update(double dt)
{
	GameObject::Update(dt);

}



// Collision things
bool Monster::CanCollideWith(GameObjectTypes type)
{
	if (type == GameObjectTypes::Obstacle ||
		type == GameObjectTypes::Block_Tile
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Basic_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Fast_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Slow_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Mother_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Weak_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Heal_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}
void Stealth_Monster::ResolveCollision(GameObject* other_object) {
	if (other_object->Type() == GameObjectTypes::Player)
	{
		//Engine::GetLogger().LogEvent("Collision with Player!");
	}

	if (static_cast<int>(other_object->Type()) >= static_cast<int>(GameObjectTypes::Bullet) &&
		static_cast<int>(other_object->Type()) <= static_cast<int>(GameObjectTypes::Bullet_End)
		)
	{
		life -= Bullet::GetDamage();

		if (other_object->Type() == GameObjectTypes::Pushing_Bullet)
		{
			Math::vec2 offset = other_object->GetVelocity();
			offset /= offset.GetLength();
			offset *= tile_size.x;

			SetPosition(Math::vec2(GetPosition().x + offset.x, GetPosition().y + offset.y));
		}

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}

		stealth = true;
		stealth_count = 0;
	}

	if (other_object->Type() == GameObjectTypes::Block_Tile ||
		other_object->Type() == GameObjectTypes::Obstacle)
	{
		//life -= 1;
		Math::rect monster_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();
		Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

		double centerX = (monster_rect.Left() + monster_rect.Right()) / 2.0 - (other_rect.Left() + other_rect.Right()) / 2.0;
		double centerY = (monster_rect.Top() + monster_rect.Bottom()) / 2.0 - (other_rect.Top() + other_rect.Bottom()) / 2.0;

		if (abs(centerX) > abs(centerY)) {
			if (centerX < 0) {
				UpdatePosition(Math::vec2{ (other_rect.Left() - monster_rect.Right()), 0.0 });
			}
			else {
				UpdatePosition(Math::vec2{ (other_rect.Right() - monster_rect.Left()), 0.0 });
			}
		}
		else {
			if (centerY < 0) {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Bottom() - monster_rect.Top()) });
			}
			else {
				UpdatePosition(Math::vec2{ 0.0, (other_rect.Top() - monster_rect.Bottom()) });
			}
		}
	}
}




// Monster state functions 

// Monster dead state functions
void Monster::State_Dead::Enter(GameObject* object)
{
	Monster* monster = static_cast<Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Monster::State_Dead::Update(GameObject* object, double dt)
{
	Monster* monster = static_cast<Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Monster::State_Dead::CheckExit(GameObject* object)
{

}

// Monster walking functions
void Monster::State_Walking::Enter(GameObject* object)
{
	Monster* monster = static_cast<Monster*>(object);

	// Path finding
	monster->path = Astar::GetInstance().GetPath();

	monster->current_tile_position = monster->path[monster->tile_index++];

	// Set Direction, speed, position...
	Math::ivec2 direction = monster->path[1] - monster->path[0];
	if (direction.x == 1)
	{
		monster->m_walking_direction = WalkingDirection::Right;
	}
	else if (direction.x == -1)
	{
		monster->m_walking_direction = WalkingDirection::Left;
	}
	else if (direction.y == 1)
	{
		monster->m_walking_direction = WalkingDirection::UP;
	}
	else if (direction.y == -1)
	{
		monster->m_walking_direction = WalkingDirection::DOWN;
	}
	else
	{
		Engine::GetLogger().LogError("Monster Direction Error!");
	}

	//Math::vec2 tile_size = Math::vec2(Engine::GetWindow().GetSize().x / 16.0, Engine::GetWindow().GetSize().y / 9.0);

	monster->SetPosition({ monster->tile_size.x * static_cast<double>(monster->current_tile_position.x), monster->tile_size.y * static_cast<double>(monster->current_tile_position.y) });
	monster->next_tile_position = monster->path[monster->tile_index++];
}
void Monster::State_Walking::Update(GameObject* object, double dt)
{
	Monster* monster = static_cast<Monster*>(object);


	Math::vec2 position = monster->GetPosition();

	if (monster->GetPosition().x > monster->next_tile_position.x * monster->tile_size.x - 20 &&
		monster->GetPosition().x < monster->next_tile_position.x * monster->tile_size.x + 20 &&
		monster->GetPosition().y > monster->next_tile_position.y * monster->tile_size.y - 20 &&
		monster->GetPosition().y < monster->next_tile_position.y * monster->tile_size.y + 20)
	{
		monster->current_tile_position = Math::ivec2(static_cast<int>(position.x / monster->tile_size.x), static_cast<int>(position.y / monster->tile_size.y));
	}

	if (monster->current_tile_position == monster->next_tile_position)
	{

		monster->next_tile_position = monster->path[(monster->tile_index++)];

		if (monster->tile_index == monster->path.size())
		{
			Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
			lifeComponent->Subtract(1);
			monster->change_state(&monster->state_dead);
		}
		Math::ivec2 direction = monster->next_tile_position - monster->current_tile_position;
		if (direction.x == 1)
		{
			monster->m_walking_direction = WalkingDirection::Right;
		}
		else if (direction.x == -1)
		{
			monster->m_walking_direction = WalkingDirection::Left;
		}
		else if (direction.y == 1)
		{
			monster->m_walking_direction = WalkingDirection::UP;
		}
		else if (direction.y == -1)
		{
			monster->m_walking_direction = WalkingDirection::DOWN;
		}
	}

	if (monster->m_walking_direction == WalkingDirection::Right)
	{
		position.x += monster->walking_speed * dt;
	}
	else if (monster->m_walking_direction == WalkingDirection::Left) {
		position.x -= monster->walking_speed * dt;
	}
	else if (monster->m_walking_direction == WalkingDirection::UP) {
		position.y += monster->walking_speed * dt;
	}
	else if (monster->m_walking_direction == WalkingDirection::DOWN) {
		position.y -= monster->walking_speed * dt;
	}

	monster->SetPosition(position);
}
void Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Basic_Monster state functions
void Basic_Monster::State_Dead::Enter(GameObject* object)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Basic_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Basic_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Basic_Monster::State_Walking::Enter(GameObject* object)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);

}
void Basic_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);


	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Basic_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Fast_Monster state functions
void Fast_Monster::State_Dead::Enter(GameObject* object)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Fast_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Fast_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Fast_Monster::State_Walking::Enter(GameObject* object)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);

	
}
void Fast_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);


	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Fast_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Slow_Monster state functions
void Slow_Monster::State_Dead::Enter(GameObject* object)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Slow_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Slow_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Slow_Monster::State_Walking::Enter(GameObject* object)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);

}
void Slow_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);

	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Slow_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Mother_Monster state functions
void Mother_Monster::State_Dead::Enter(GameObject* object)
{
	Mother_Monster* monster = static_cast<Mother_Monster*>(object);
	--remaining_monsters;


	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Mother_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Mother_Monster* monster = static_cast<Mother_Monster*>(object);
	Engine::GetLogger().LogDebug("Mother monster state_dead Update");


	monster->resisting_count += dt;

	if (monster->dead_by_player)
	{
		if (monster->resisting_count >= monster->resisting_time / static_cast<double>(baby))
		{
			new Weak_Monster(monster);
			++monster->baby_count;
			monster->resisting_count = 0;
		}

		if (monster->baby_count >= monster->baby)
		{
			monster->Destroy();
		}
	}
	else
	{
		if (monster->resisting_count >= monster->resisting_time)
		{
			monster->Destroy();
		}
	}
}
void Mother_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Mother_Monster::State_Walking::Enter(GameObject* object)
{
	Mother_Monster* monster = static_cast<Mother_Monster*>(object);

}
void Mother_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Mother_Monster* monster = static_cast<Mother_Monster*>(object);

	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Mother_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Weak_Monster state functions
void Weak_Monster::State_Dead::Enter(GameObject* object)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Weak_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Weak_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Weak_Monster::State_Walking::Enter(GameObject* object)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);

}
void Weak_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);


	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Weak_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Heal_Monster state functions
void Heal_Monster::State_Dead::Enter(GameObject* object)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Heal_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Heal_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Heal_Monster::State_Walking::Enter(GameObject* object)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);

}
void Heal_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);
	

	for (Monster* target : Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetMonstersInRange(monster, range))
	{
		//Engine::GetLogger().LogDebug(std::to_string(target->GetLife()) + " / " + std::to_string(target->GetMaxLife()));
		if (target->GetLife() < target->GetMaxLife() && target->GetLife() >= 0)
		{
			monster->change_state(&monster->state_healing);
		}
	}

	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);
}
void Heal_Monster::State_Walking::CheckExit(GameObject* object)
{

}

void Heal_Monster::State_Healing::Enter(GameObject* object)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);

	monster->healing_count = 0;
}
void Heal_Monster::State_Healing::Update(GameObject* object, double dt)
{
	Heal_Monster* monster = static_cast<Heal_Monster*>(object);

	monster->healing_count += dt;

	if (monster->healing_count >= monster->healing_cool_time)
	{
		Monster* target = Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->GetClosestMonster(monster);
		target->Heal(monster->heal_value);
		monster->change_state(&monster->state_walking);
	}
}
void Heal_Monster::State_Healing::CheckExit(GameObject* object)
{

}


// Weak_Monster state functions
void Stealth_Monster::State_Dead::Enter(GameObject* object)
{
	Stealth_Monster* monster = static_cast<Stealth_Monster*>(object);
	--remaining_monsters;



	monster->RemoveGOComponent<GAM200::RectCollision>();

	//monster->GetGOComponent<GAM200::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}
void Stealth_Monster::State_Dead::Update(GameObject* object, double dt)
{
	Stealth_Monster* monster = static_cast<Stealth_Monster*>(object);

	monster->resisting_count += dt;
	if (monster->resisting_count >= monster->resisting_time) {
		monster->Destroy();
	}
}
void Stealth_Monster::State_Dead::CheckExit(GameObject* object)
{

}

void Stealth_Monster::State_Walking::Enter(GameObject* object)
{
	Stealth_Monster* monster = static_cast<Stealth_Monster*>(object);

}
void Stealth_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Stealth_Monster* monster = static_cast<Stealth_Monster*>(object);


	Math::vec2 position = monster->GetPosition();

	Math::vec2 next_tile = Math::vec2{ (monster->next_tile_position.x + 1.0 / 2) * monster->tile_size.x - monster->size_x / 2, (monster->next_tile_position.y + 1.0 / 2) * monster->tile_size.y - monster->size_y / 2 };

	Math::vec2 direction = next_tile - position;
	double distance = direction.GetLength();

	if (distance > 0.0) {
		direction /= distance;

		if (distance < 20.0) {
			monster->current_tile_position = Math::ivec2(static_cast<int>(next_tile.x / monster->tile_size.x), static_cast<int>(next_tile.y / monster->tile_size.y));
			monster->next_tile_position = monster->path[(monster->tile_index++)];

			if (monster->tile_index == monster->path.size()) {
				Life* lifeComponent = Engine::GetGameStateManager().GetGSComponent<Life>();
				lifeComponent->Subtract(1);
				monster->change_state(&monster->state_dead);
			}
		}
	}

	position += direction * monster->walking_speed * dt;

	monster->SetPosition(position);

	if (monster->stealth)
	{
		monster->stealth_count += dt;
		
		if (monster->stealth_count >= monster->stealth_time)
			monster->stealth = false;
	}
}
void Stealth_Monster::State_Walking::CheckExit(GameObject* object)
{

}


// File parsing things
int		Monster::remaining_monsters = 0;

int     Monster::damage = 0;
int     Monster::max_life = 0;
int     Monster::score = 0;
int     Monster::gold = 0;
double  Monster::speed_scale = 0.0f;

int     Basic_Monster::damage = 0;
int     Basic_Monster::max_life = 0;
int     Basic_Monster::score = 0;
int     Basic_Monster::gold = 0;
double  Basic_Monster::speed_scale = 0.0f;

int     Slow_Monster::damage = 0;
int     Slow_Monster::max_life = 0;
int     Slow_Monster::score = 0;
int     Slow_Monster::gold = 0;
double  Slow_Monster::speed_scale = 0.0f;

int     Fast_Monster::damage = 0;
int     Fast_Monster::max_life = 0;
int     Fast_Monster::score = 0;
int     Fast_Monster::gold = 0;
double  Fast_Monster::speed_scale = 0.0f;

int     Mother_Monster::damage = 0;
int     Mother_Monster::max_life = 0;
int     Mother_Monster::score = 0;
int     Mother_Monster::gold = 0;
double  Mother_Monster::speed_scale = 0.0f;

int     Weak_Monster::damage = 0;
int     Weak_Monster::max_life = 0;
int     Weak_Monster::score = 0;
int     Weak_Monster::gold = 0;
double  Weak_Monster::speed_scale = 0.0f;

int     Heal_Monster::damage = 0;
int     Heal_Monster::max_life = 0;
int     Heal_Monster::score = 0;
int     Heal_Monster::gold = 0;
double  Heal_Monster::speed_scale = 0.0f;

int     Stealth_Monster::damage = 0;
int     Stealth_Monster::max_life = 0;
int     Stealth_Monster::score = 0;
int     Stealth_Monster::gold = 0;
double  Stealth_Monster::speed_scale = 0.0f;



void MonsterFactory::InitBasicMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Basic_Monster::max_life;
		file >> Basic_Monster::damage;
		file >> Basic_Monster::speed_scale;
		file >> Basic_Monster::gold;
		file >> Basic_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

	//new Basic_Monster();
}

void MonsterFactory::InitFastMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Fast_Monster::max_life;
		file >> Fast_Monster::damage;
		file >> Fast_Monster::speed_scale;
		file >> Fast_Monster::gold;
		file >> Fast_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

	//new Fast_Monster();
}

void MonsterFactory::InitSlowMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Slow_Monster::max_life;
		file >> Slow_Monster::damage;
		file >> Slow_Monster::speed_scale;
		file >> Slow_Monster::gold;
		file >> Slow_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

	//new Slow_Monster();
}

void MonsterFactory::InitMotherMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Mother_Monster::max_life;
		file >> Mother_Monster::damage;
		file >> Mother_Monster::speed_scale;
		file >> Mother_Monster::gold;
		file >> Mother_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}


}

void MonsterFactory::InitWeakMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Weak_Monster::max_life;
		file >> Weak_Monster::damage;
		file >> Weak_Monster::speed_scale;
		file >> Weak_Monster::gold;
		file >> Weak_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

	//new Weak_Monster();
}

void MonsterFactory::InitHealMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Heal_Monster::max_life;
		file >> Heal_Monster::damage;
		file >> Heal_Monster::speed_scale;
		file >> Heal_Monster::gold;
		file >> Heal_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

}

void MonsterFactory::InitStealthMonsterFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Stealth_Monster::max_life;
		file >> Stealth_Monster::damage;
		file >> Stealth_Monster::speed_scale;
		file >> Stealth_Monster::gold;
		file >> Stealth_Monster::score;
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}

}