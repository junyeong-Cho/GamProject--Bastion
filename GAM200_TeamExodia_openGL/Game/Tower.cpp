

#include "Tower.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "Gold.h"
#include "Map.h"

Tower::Tower(Math::vec2 position, int direction) : GameObject(position), direction(direction) {
	charging_color = { 0.0f, 0.0f, 1.0f };
	attack_color = { 0.0f, 0.0f, 0.0f };
	color = charging_color;

	SetPosition(position);

	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	//size_x = window_size.x / Map::GetInstance().GetSize().x;
	//size_y = window_size.y / Map::GetInstance().GetSize().y;
	//size_x /= 2;
	size_x = 80;
	size_y = 80;

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

	AddGOComponent(new GAM200::RectCollision(Math::irect{ {0, 0}, {size_x, size_y} }, this));

	current_state = &state_charging;
	current_state->Enter(this);

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



Basic_Tower::Basic_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Double_Tower::Double_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Triple_Tower::Triple_Tower(Math::vec2 position, int direction) : Tower(position, direction) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);

	current_state = &state_charging;
	current_state->Enter(this);

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}





void Tower::State_Charging::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->charging_color;
}
void Tower::State_Charging::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	tower -> attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);
	}
}
void Tower::State_Charging::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);

}


void Tower::State_Attacking::Enter(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	tower->color = tower->attack_color;
}
void Tower::State_Attacking::Update(GameObject* object, double dt) {
	Tower* tower = static_cast<Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });
	
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity));
	new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);
	tower->change_state(&tower->state_charging);
}
void Tower::State_Attacking::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	
}





void Basic_Tower::State_Charging::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->charging_color;
}
void Basic_Tower::State_Charging::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);
	}
}
void Basic_Tower::State_Charging::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}


void Basic_Tower::State_Attacking::Enter(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);
	tower->color = tower->attack_color;
}
void Basic_Tower::State_Attacking::Update(GameObject* object, double dt) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size_x / 2, tower->GetPosition().y + tower->size_y / 2 });

	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity));
	new Bullet(tower_position, tower->bullet_direction * Bullet::DefaultVelocity);
	tower->change_state(&tower->state_charging);
}
void Basic_Tower::State_Attacking::CheckExit(GameObject* object) {
	Basic_Tower* tower = static_cast<Basic_Tower*>(object);

}




void Double_Tower::State_Charging::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->charging_color;
}
void Double_Tower::State_Charging::Update(GameObject* object, double dt) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);
	}
}
void Double_Tower::State_Charging::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}


void Double_Tower::State_Attacking::Enter(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);
	tower->color = tower->attack_color;
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
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(point1, tower->bullet_direction * Bullet::DefaultVelocity));
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(point2, tower->bullet_direction * Bullet::DefaultVelocity));

	tower->change_state(&tower->state_charging);
}
void Double_Tower::State_Attacking::CheckExit(GameObject* object) {
	Double_Tower* tower = static_cast<Double_Tower*>(object);

}




void Triple_Tower::State_Charging::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->charging_color;
}
void Triple_Tower::State_Charging::Update(GameObject* object, double dt) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

	tower->attack_count += dt;

	if (tower->attack_count >= tower->attack_delay) {
		tower->attack_count = 0;
		tower->change_state(&tower->state_attacking);
	}
}
void Triple_Tower::State_Charging::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}


void Triple_Tower::State_Attacking::Enter(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);
	tower->color = tower->attack_color;
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

	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, bullet_direction_left * Bullet::DefaultVelocity));
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, bullet_direction_middle * Bullet::DefaultVelocity));
	//Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, bullet_direction_right * Bullet::DefaultVelocity));

	tower->change_state(&tower->state_charging);
}
void Triple_Tower::State_Attacking::CheckExit(GameObject* object) {
	Triple_Tower* tower = static_cast<Triple_Tower*>(object);

}