
#include "Monster.h"

#include "Particles.h"

#include "../Engine/GameObjectManager.h"
#include "../Engine/DrawShape.h"
#include "../Engine/Collision.h"
#include "../Engine/Audio.h"
#include "../Engine/Particle.h"

#include "../Component/Gold.h"

int Monster::remaining_monster = 0;

Monster::Monster(MonsterInfo info) : GameObject(Map::middle_upper_left), info(info)
{
	SetPosition(Map::middle_upper_left);
	SetVelocity({ 0, -speed * info.speed_scale });

	AddGOComponent(new GAM200::CircleCollision(radius, this));
	Engine::GetGameStateManager().GetGSComponent<GAM200::GameObjectManager>()->Add(this);

	++remaining_monster;
}

Monster::Monster(MonsterInfo info, Math::vec2 position, Math::vec2 direction) : GameObject(position), info(info)
{
	SetPosition(position);
	SetVelocity({ direction.x * speed * info.speed_scale, direction.y * speed * info.speed_scale });
}

Monster::~Monster() 
{
	Engine::GetGameStateManager().GetGSComponent<Gold>()->Earn(1);
	RemoveGOComponent<GAM200::CircleCollision>();
	--remaining_monster;
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

	if (info.life <= 0)
	{
		Destroy();

		//Sound
		GAM200::SoundEffect::Monster_Die_2().play();
	}
}

// Draw
void Monster::Draw(Math::TransformationMatrix camera_matrix)
{
	//GAM200::DrawShape shape;
	//shape.SetColor(0.0f, 0.8f, 0.8f, 1.0f);

	Math::vec2 position = GetPosition();
	default_enemy->Draw(static_cast<int>(position.x) - 528/8, static_cast<int>(position.y), 528/4, 350/4);
	//shape.DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(radius), static_cast<int>(radius));
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

void Monster::TakeDamage(int damage) 
{ 
	info.life -= damage; 
	Engine::GetLogger().LogDebug(std::to_string(damage) + "damage! Remaining hp: " + std::to_string(info.life)); 

	Math::vec2 particle_posistion = GetPosition();


	
	Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Hit>>()->Emit(1, particle_posistion, { 0, 0 }, { 0, 0 }, 3.14159265358979323846 / 2);
	//Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::MeteorBit>>()->Emit(5, particle_posistion, { 0, 0 }, { 0, 100 }, 3.14159265358979323846 / 3);
}
