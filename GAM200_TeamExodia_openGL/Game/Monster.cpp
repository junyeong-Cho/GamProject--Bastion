
#include "Monster.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"

Monster::Monster(MonsterInfo info) : GameObject(Map::middle_upper_left), info(info)
{
	SetPosition(Map::middle_upper_left);
	SetVelocity({ 0, -speed * info.speed_scale });
	//AddGOComponent(new GAM200::RectCollision(Math::irect{ Math::ivec2{0, 0}, Math::ivec2{size_x, size_y} }, this));
	AddGOComponent(new GAM200::CircleCollision(radius, this));
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Monster::Monster(MonsterInfo info, Math::vec2 position, Math::vec2 direction) : GameObject(position), info(info)
{
	SetPosition(position);
	SetVelocity({ direction.x * speed * info.speed_scale, direction.y * speed * info.speed_scale });
}


void Monster::Update(double dt)
{
	// Update Position 
	GameObject::Update(dt);

	// Update Velocity
	if (IsInside(Map::outer_lower_left))
	{
		SetVelocity({ speed * info.speed_scale, 0 });
	}
	else if (IsInside(Map::outer_lower_right))
	{
		SetVelocity({ 0, speed * info.speed_scale });
	}
	else if (IsInside(Map::outer_upper_right))
	{
		SetVelocity({ -speed * info.speed_scale, 0 });
	}
	else if (IsInside(Map::outer_upper_left))
	{
		SetVelocity({ 0, -speed * info.speed_scale });
	}
}

// Draw
void Monster::Draw(Math::TransformationMatrix camera_matrix)
{
	GAM200::DrawShape shape;
	shape.SetColor(0.0f, 0.8f, 0.8f, 1.0f);

	Math::vec2 position = GetPosition();
	shape.DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius), static_cast<int>(radius));
}

// Check to change direction
bool Monster::IsInside(Math::vec2 target_position) const
{
	Math::vec2 positioin = GetPosition();

	if (positioin.x >= target_position.x - offset / 2 &&
		positioin.x <= target_position.x + offset / 2&&
		positioin.y >= target_position.y - offset / 2 &&
		positioin.y <= target_position.y + offset / 2
		)
		return true;
	else
		return false;
}