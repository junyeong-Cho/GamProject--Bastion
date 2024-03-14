
#include "Monster.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/DrawShape.h"

Monster::Monster(int life, double speed_scale) : GameObject(middle_upper_left), life(life), speed_scale(speed_scale)
{
	SetPosition(middle_upper_left);
	SetVelocity({ 0, -speed * speed_scale });

	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);
}

Monster::Monster(int life, double speed_scale, Math::vec2 position, Math::vec2 direction) : GameObject(position), life(life), speed_scale(speed_scale)
{
	SetPosition(position);
	SetVelocity({ direction.x * speed * speed_scale, direction.y * speed * speed_scale });
}


void Monster::Update(double dt)
{
	// Update Position 
	GameObject::Update(dt);

	// Update Velocity
	if (IsInside(outer_lower_left))
	{
		SetVelocity({ speed * speed_scale, 0 });
	}
	else if (IsInside(outer_lower_right))
	{
		SetVelocity({ 0, speed * speed_scale });
	}
	else if (IsInside(outer_upper_right))
	{
		SetVelocity({ -speed * speed_scale, 0 });
	}
	else if (IsInside(outer_upper_left))
	{
		SetVelocity({ 0, -speed * speed_scale });
	}
}

// Draw
void Monster::Draw(Math::TransformationMatrix camera_matrix)
{
	GAM200::DrawShape shape;
	shape.SetColor(0.0, 0.8, 0.8, 1.0);
	Math::vec2 position = Math::vec2(GetPosition().x - size / 2.0, GetPosition().y - size / 2.0);
	shape.DrawRectangle(position.x, position.y, size, size);
}

// Check to change direction
bool Monster::IsInside(Math::vec2 target_position) const
{
	Math::vec2 positioin = Math::vec2(GetPosition().x + size / 2.0, GetPosition().y + size / 2.0);

	if (positioin.x > target_position.x - offset &&
		positioin.x < target_position.x + offset &&
		positioin.y > target_position.y - offset &&
		positioin.y < target_position.y + offset
		)
	{
		Engine::GetLogger().LogDebug(std::to_string(GetPosition().x) + ", " + std::to_string(GetPosition().y) + "/t/tChange Direction!");
		return true;
	}
	else
		return false;
}