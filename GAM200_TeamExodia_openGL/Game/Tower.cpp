

#include "Tower.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "Gold.h"
#include "Map.h"

Tower::Tower(Math::vec2 position) : GameObject(position) {
	charging_color = { 0.0f, 0.0f, 1.0f };
	attack_color = { 0.0f, 0.0f, 0.0f };
	color = charging_color;

	SetPosition(position);

	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	size_x = window_size.x / Map::GetInstance().GetSize().x;
	size_y = window_size.y / Map::GetInstance().GetSize().y;
	size_x /= 2;
	size_y /= 2;
	AddGOComponent(new GAM200::RectCollision(Math::irect{ {0, 0}, {size_x, size_y} }, this));

	current_state = &state_charging;
	current_state->Enter(this);
}

void Tower::Update(double dt) {
	GameObject::Update(dt);

}

void Tower::Draw(Math::TransformationMatrix camera_matrix) {
	

	if (set_basic_tower == true)
	{
		c.Draw(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), size_x, size_y);
	}

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
	Math::ivec2 window_size = Engine::GetWindow().GetSize();
	Math::vec2 mouse_position = Engine::GetInput().GetMousePosition();

	Math::vec2 real_mouse_position = Math::vec2({ mouse_position.x, window_size.y - mouse_position.y });
	Math::vec2 bullet_direction = Math::vec2({ real_mouse_position.x - tower_position.x, real_mouse_position.y - tower_position.y });
	bullet_direction /= bullet_direction.GetLength();

	bullet_direction = Math::vec2{ 0, -1 };

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, bullet_direction * Bullet::DefaultVelocity));
	tower->change_state(&tower->state_charging);
	//GameObject* target = GAM200::GameObjectManager().GetClosestObject(tower);
	//if (target != nullptr) {
	//	Engine::GetLogger().LogDebug("Target on!\n");
	//	Math::vec2 tower_position = Math::vec2({ tower->GetPosition().x + tower->size / 2, tower->GetPosition().y + tower->size / 2 });
	//	Math::ivec2 window_size = Engine::GetWindow().GetSize();

	//	Math::vec2 target_position = target->GetPosition();

	//	Math::vec2 bullet_direction = Math::vec2({ target_position.x - tower_position.x, target_position.y - tower_position.y });
	//	bullet_direction /= bullet_direction.GetLength();

	//	//bullet_direction = { 0,-1 };
	//	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(new Bullet(tower_position, bullet_direction * Bullet::DefaultVelocity));

	//	tower->change_state(&tower->state_charging);
	//}
}
void Tower::State_Attacking::CheckExit(GameObject* object) {
	Tower* tower = static_cast<Tower*>(object);
	
	
}

Basic_Tower:: Basic_Tower(Math::vec2 position) : Tower(position) {
	charging_color = { 0.f, 0.f, 0.6f };
	attack_color = { 0.0f, 0.0f, 0.0f };

	set_basic_tower = true;

	Gold* goldComponent = Engine::GetGameStateManager().GetGSComponent<Gold>();
	goldComponent->Subtract(cost);
}