

#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

#include "Bullet.h"
#include "Tower.h"
#include "Gold.h"
#include "Map.h"


Tower::Tower(Math::vec2 position, int direction) : GameObject(position), direction(direction) {
	charging_color = { 0.0f, 0.0f, 1.0f };
	attack_color = { 0.0f, 0.0f, 0.0f };
	color = charging_color;

	SetPosition(position);

	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		bullet_direction = Math::vec2(1, 0);
		four_way[1] = true;
		break;
	case 1:
		bullet_direction = Math::vec2(-1, 0);
		four_way[3] = true;
		break;
	case 2:
		bullet_direction = Math::vec2(0, 1);
		four_way[0] = true;
		break;
	case 3:
		bullet_direction = Math::vec2(0, -1);
		four_way[2] = true;
		break;

	}
	hp = max_hp;

	//AddGOComponent(new GAM200::RectCollision(Math::irect{ {0, 0}, {size_x, size_y} }, this));

	//current_state = &state_charging;
	//current_state->Enter(this);

}
void Tower::Update(double dt) 
{
	GameObject::Update(dt);

}
void Tower::Tower_Destroy()
{
	Destroy();
	RemoveGOComponent<GAM200::RectCollision>();
}
void Tower::Draw(Math::TransformationMatrix camera_matrix) {
	

	if (four_way[0] == true)
	{
		c_up.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[1] == true)
	{
		c_right.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[2] == true)
	{
		c_down.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}
	else if (four_way[3] == true)
	{
		c_left.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}

}

bool Tower::CanCollideWith(GameObjectTypes type)
{
	if (type == GameObjectTypes::Basic_Monster ||
		type == GameObjectTypes::Fast_Monster ||
		type == GameObjectTypes::Slow_Monster ||
		type == GameObjectTypes::Weak_Monster //|| type == GameObjectTypes::Block_Tile
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	switch (other_object->Type())
	{
	case GameObjectTypes::Basic_Monster:
		Engine::GetLogger().LogDebug("Basic monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Fast_Monster:
		Engine::GetLogger().LogDebug("Fast monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Slow_Monster:
		Engine::GetLogger().LogDebug("Slow monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Weak_Monster:
		Engine::GetLogger().LogDebug("Weak monster detected!");
		change_state(&this->state_attacking);
		break;

	default:

		break;
	}
}


// Constructor of Basic_Tower
Basic_Tower::Basic_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	Math::ivec2 point1{0, 0};
	Math::ivec2 point2{ size_x, size_y };

	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 3 * size_y / 8}, Math::ivec2{3 * size_x, 5 * size_y / 8} }, this));
		break;

	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-2 * size_x, 3 * size_y / 8}, Math::ivec2{size_x, 5 * size_y / 8} }, this));
		break;

	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, 0}, Math::ivec2{5 * size_x / 8, 3 * size_y} }, this));
		break;

	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, -2 * size_y}, Math::ivec2{5 * size_x / 8, size_y} }, this));
		break;
	}

	

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

// Constructor of Double_Tower
Double_Tower::Double_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 3 * size_y / 8}, Math::ivec2{3 * size_x, 5 * size_y / 8} }, this));
		break;

	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-2 * size_x, 3 * size_y / 8}, Math::ivec2{size_x, 5 * size_y / 8} }, this));
		break;

	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, 0}, Math::ivec2{5 * size_x / 8, 3 * size_y} }, this));
		break;

	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, -2 * size_y}, Math::ivec2{5 * size_x / 8, size_y} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

// Constructor of Triple_Tower
Triple_Tower::Triple_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	// RIGHT, LEFT, UP, DOWN
	switch (direction)
	{
	case 0:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 3 * size_y / 8}, Math::ivec2{3 * size_x, 5 * size_y / 8} }, this));
		break;

	case 1:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{-2 * size_x, 3 * size_y / 8}, Math::ivec2{size_x, 5 * size_y / 8} }, this));
		break;

	case 2:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, 0}, Math::ivec2{5 * size_x / 8, 3 * size_y} }, this));
		break;

	case 3:
		AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{3 * size_x / 8, -2 * size_y}, Math::ivec2{5 * size_x / 8, size_y} }, this));
		break;
	}

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}


// Collision functions
bool Basic_Tower::CanCollideWith(GameObjectTypes type)
{
	if (type == GameObjectTypes::Basic_Monster ||
		type == GameObjectTypes::Fast_Monster ||
		type == GameObjectTypes::Slow_Monster ||
		type == GameObjectTypes::Weak_Monster //|| type == GameObjectTypes::Block_Tile
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Basic_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	switch (other_object->Type())
	{
	case GameObjectTypes::Basic_Monster:
		Engine::GetLogger().LogDebug("Basic monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Fast_Monster:
		Engine::GetLogger().LogDebug("Fast monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Slow_Monster:
		Engine::GetLogger().LogDebug("Slow monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Weak_Monster:
		Engine::GetLogger().LogDebug("Weak monster detected!");
		change_state(&this->state_attacking);
		break;

	default:

		break;
	}
}

bool Double_Tower::CanCollideWith(GameObjectTypes type)
{
	if (type == GameObjectTypes::Basic_Monster ||
		type == GameObjectTypes::Fast_Monster ||
		type == GameObjectTypes::Slow_Monster ||
		type == GameObjectTypes::Weak_Monster //|| type == GameObjectTypes::Block_Tile
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Double_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	switch (other_object->Type())
	{
	case GameObjectTypes::Basic_Monster:
		Engine::GetLogger().LogDebug("Basic monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Fast_Monster:
		Engine::GetLogger().LogDebug("Fast monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Slow_Monster:
		Engine::GetLogger().LogDebug("Slow monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Weak_Monster:
		Engine::GetLogger().LogDebug("Weak monster detected!");
		change_state(&this->state_attacking);
		break;

	default:

		break;
	}
}

bool Triple_Tower::CanCollideWith(GameObjectTypes type)
{
	if (type == GameObjectTypes::Basic_Monster ||
		type == GameObjectTypes::Fast_Monster ||
		type == GameObjectTypes::Slow_Monster ||
		type == GameObjectTypes::Weak_Monster //|| type == GameObjectTypes::Block_Tile
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Triple_Tower::ResolveCollision(GameObject* other_object)
{
	Math::rect tower_rect = GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	Math::rect other_rect = other_object->GetGOComponent<GAM200::RectCollision>()->WorldBoundary();

	if (attack_ready == false)
		return;

	switch (other_object->Type())
	{
	case GameObjectTypes::Basic_Monster:
		Engine::GetLogger().LogDebug("Basic monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Fast_Monster:
		Engine::GetLogger().LogDebug("Fast monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Slow_Monster:
		Engine::GetLogger().LogDebug("Slow monster detected!");
		attack_ready = false;
		change_state(&this->state_attacking);
		break;

	case GameObjectTypes::Weak_Monster:
		Engine::GetLogger().LogDebug("Weak monster detected!");
		change_state(&this->state_attacking);
		break;

	default:

		break;
	}
}


// State functions charging
void Tower::State_Charging::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Tower::State_Charging::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	// Increment the attack count based on the dt
	tower -> attack_count += dt;

	// Attack and change state to state_attacking
	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Tower::State_Charging::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);

}

// State functions for attacking
void Tower::State_Attacking::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Tower::State_Attacking::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });
	
	// Create a new bullet at the tower position with specified direction
	new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);

	// Change state to state_charging
	tower->change_state(&tower->state_charging);
}
void Tower::State_Attacking::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	
}




// State functions for charging of Basic_Tower
void Basic_Tower::State_Charging::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Basic_Tower::State_Charging::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Basic_Tower::State_Charging::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}

// State functions for Attacking of Basic_Tower
void Basic_Tower::State_Attacking::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Basic_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });

	new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);
	tower->change_state(&tower->state_charging);
}
void Basic_Tower::State_Attacking::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}




// State functions for charging of Double_Tower
void Double_Tower::State_Charging::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
	tower->attack_count = 0;
}
void Double_Tower::State_Charging::Update(GameObject* object, double dt) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Double_Tower::State_Charging::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}

// State functions for Attacking of Double_Tower
void Double_Tower::State_Attacking::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_ready = false;
}
void Double_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });
	Math::vec2 point1 = Math::vec2(tower_position.x, tower_position.y);
	Math::vec2 point2 = Math::vec2(tower_position.x, tower_position.y);
	Math::vec2 offset(tower->size_x * 0.1, tower->size_y * 0.1);
	// RIGHT, LEFT, UP, DOWN
	switch (tower->direction)
	{
	case 0:
		point1 += Math::vec2(0, offset.y);
		point2 += Math::vec2(0, -offset.y);
		break;
	case 1:
		point1 += Math::vec2(0, offset.y);
		point2 += Math::vec2(0, -offset.y);
		break;
	case 2:
		point1 += Math::vec2(offset.x, 0);
		point2 += Math::vec2(-offset.x, 0);
		break;
	case 3:
		point1 += Math::vec2(offset.x, 0);
		point2 += Math::vec2(-offset.x, 0);
		break;
	}

	new Bullet(point1, tower->bullet_direction * Bullet::DefaultVelocity);
	new Bullet(point2, tower->bullet_direction * Bullet::DefaultVelocity);

	tower->change_state(&tower->state_charging);
}
void Double_Tower::State_Attacking::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}




// State functions for charging of Triple_Tower
void Triple_Tower::State_Charging::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->charging_color;
	tower->attack_ready = false;
}
void Triple_Tower::State_Charging::Update(GameObject* object, double dt) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_ready = true;
		/*tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);*/
	}
}
void Triple_Tower::State_Charging::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}

// State functions for Attacking of Triple_Tower
void Triple_Tower::State_Attacking::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->attack_color;
	tower->attack_count = 0;
}
void Triple_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });

	Math::vec2 offset(tower->size_x * 0.1, tower->size_y * 0.1);

	Math::vec2 bullet_direction_left;
	Math::vec2 bullet_direction_right;
	Math::vec2 bullet_direction_middle = tower->bullet_direction;

	// RIGHT, LEFT, UP, DOWN
	switch (tower->direction)
	{
	case 0:
		bullet_direction_left = Math::vec2(tower->size_x, offset.y);
		bullet_direction_right = Math::vec2(tower->size_x, -offset.y);
		break;
	case 1:
		bullet_direction_left = Math::vec2(-tower->size_x, offset.y);
		 bullet_direction_right = Math::vec2(-tower->size_x, -offset.y);
		break;
	case 2:
		bullet_direction_left = Math::vec2(offset.x, tower->size_y);
		bullet_direction_right = Math::vec2(-offset.x, tower->size_y);
		break;
	case 3:
		bullet_direction_left = Math::vec2(offset.x, -tower->size_y);
		bullet_direction_right = Math::vec2(-offset.x, -tower->size_y);
		break;
	}

	bullet_direction_left.Normalize();
	bullet_direction_right.Normalize();

	new Bullet(tower_position, bullet_direction_left * Bullet::DefaultVelocity);
	new Bullet(tower_position, bullet_direction_middle * Bullet::DefaultVelocity);
	new Bullet(tower_position, bullet_direction_right * Bullet::DefaultVelocity);

	tower->change_state(&tower->state_charging);
}
void Triple_Tower::State_Attacking::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}







int Tower::cost = 0;
double Tower::attack_delay = 0.0;
int Tower::max_hp = 0;

int Basic_Tower::cost = 0;
double Basic_Tower::attack_delay = 0.0;
int Basic_Tower::max_hp = 0;

int Double_Tower::cost = 0;
double Double_Tower::attack_delay = 0.0;
int Double_Tower::max_hp = 0;

int Triple_Tower::cost = 0;
double Triple_Tower::attack_delay = 0.0;
int Triple_Tower::max_hp = 0;


// File parsing from the txt file
void TowerFactory::InitBasicTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Basic_Tower::cost;

		file >> Basic_Tower::attack_delay;

		file >> Basic_Tower::max_hp;
	}

}

// File parsing from the txt file
void TowerFactory::InitDoubleTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Double_Tower::cost;

		file >> Double_Tower::attack_delay;

		file >> Double_Tower::max_hp;
	}

}

// File parsing from the txt file
void TowerFactory::InitTripleTowerFromFile(const std::string& filePath) {
	std::ifstream file(filePath);

	if (file.is_open())
	{
		file >> Triple_Tower::cost;

		file >> Triple_Tower::attack_delay;

		file >> Triple_Tower::max_hp;
	}

}