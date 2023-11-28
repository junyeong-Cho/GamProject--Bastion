

#include <iostream>
#include <fstream>
#include <string>

#include "../Engine/GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "../Engine/DrawShape.h"

#include "Monster.h"
#include "States.h"

#include "Score.h"
#include "Gold.h"
#include "Life.h"

#include "Bullet.h"
#include "Map.h"



int Monster::remaining_monsters = 0;


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

void Monster::ResolveCollision(GameObject* other_object) {

	if (other_object->Type() == GameObjectTypes::Player)
	{

	}
	else if (other_object->Type() == GameObjectTypes::Bullet)
	{
		life -= Bullet::GetDamage();

		if (life <= 0) {
			Score* scoreComponent = Engine::GetGameStateManager().GetGSComponent<Score>();
			Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();

			scoreComponent->Add(this->real_score);
			goldComponent->Add(this->real_gold);

			change_state(&state_dead);
		}
	}
	else if (other_object->Type() == GameObjectTypes::Block_Tile)
	{
		Engine::GetLogger().LogDebug("Resolve Collision Block Tile!");
	}
}


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
	// Update monster's current tile position
	/*static bool change_direction = false;

	switch (monster->m_walking_direction) {
	case(WalkingDirection::Right):
		if (monster->boundary.Left() > monster->next_tile_position.x * tile_size.x)
			change_direction = true;
		break;
	case(WalkingDirection::Left):
		if (monster->boundary.Right() < (monster->next_tile_position.x + 1) * tile_size.x)
			change_direction = true;
		break;
	case(WalkingDirection::UP):
		if (monster->boundary.Bottom() > monster->next_tile_position.y * tile_size.y)
			change_direction = true;
		break;
	case(WalkingDirection::DOWN):
		if (monster->boundary.Top() < (monster->next_tile_position.y + 1) * tile_size.y)
			change_direction = true;
		break;
	}

	if (change_direction) {
		std::cout << "Change Detected!\n";
		monster->current_tile_position = Math::ivec2(static_cast<int>(position.x / tile_size.x), static_cast<int>(position.y / tile_size.y));
		change_direction = false;
	}*/
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




// Constructors


Basic_Monster::Basic_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_damage = Basic_Monster::damage;
	real_speed_scale = Basic_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Basic_Monster::score;
	real_gold = Basic_Monster::gold;

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Basic_Monster::Update(double dt)
{
	GameObject::Update(dt);

}


Fast_Monster::Fast_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_damage = Fast_Monster::damage;
	real_speed_scale = Fast_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Fast_Monster::score;
	real_gold = Fast_Monster::gold;

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Fast_Monster::Update(double dt)
{
	GameObject::Update(dt);

}



Slow_Monster::Slow_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_damage = Slow_Monster::damage;
	real_speed_scale = Slow_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Slow_Monster::score;
	real_gold = Slow_Monster::gold;

	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Slow_Monster::Update(double dt)
{
	GameObject::Update(dt);

}



Weak_Monster::Weak_Monster(Math::vec2 position) : Monster(position) {
	life = max_life;
	real_damage = Weak_Monster::damage;
	real_speed_scale = Weak_Monster::speed_scale;
	walking_speed *= speed_scale;
	real_score = Weak_Monster::score;
	real_gold = Weak_Monster::gold;


	current_state = &state_walking;
	current_state->Enter(this);
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}
void Weak_Monster::Update(double dt)
{
	GameObject::Update(dt);

}












// State function things



// Basic_Monster dead state functions
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

// Basic_Monster walking state functions
void Basic_Monster::State_Walking::Enter(GameObject* object)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);

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
void Basic_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Basic_Monster* monster = static_cast<Basic_Monster*>(object);


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
void Basic_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Fast_Monster dead state functions
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

// Fast_Monster walking state functions
void Fast_Monster::State_Walking::Enter(GameObject* object)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);

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
void Fast_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Fast_Monster* monster = static_cast<Fast_Monster*>(object);


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
void Fast_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Slow_Monster dead state functions
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

// Slow_Monster walking state functions
void Slow_Monster::State_Walking::Enter(GameObject* object)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);

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
void Slow_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Slow_Monster* monster = static_cast<Slow_Monster*>(object);


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
void Slow_Monster::State_Walking::CheckExit(GameObject* object)
{

}

// Weak_Monster dead state functions
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

// Weak_Monster walking state functions
void Weak_Monster::State_Walking::Enter(GameObject* object)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);

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
void Weak_Monster::State_Walking::Update(GameObject* object, double dt)
{
	Weak_Monster* monster = static_cast<Weak_Monster*>(object);


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
void Weak_Monster::State_Walking::CheckExit(GameObject* object)
{

}













// File parsing things

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

int     Weak_Monster::damage = 0;
int     Weak_Monster::max_life = 0;
int     Weak_Monster::score = 0;
int     Weak_Monster::gold = 0;
double  Weak_Monster::speed_scale = 0.0f;


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

void MonsterFactory::InitWeakMonstserFromFile(const std::string& filePath)
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