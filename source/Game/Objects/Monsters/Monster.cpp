
#include "Monster.h"

#include "Game/Particles.h"

#include "Engine/GameObjectManager.h"
#include "Engine/DrawShape.h"
#include "Engine/Collision.h"
#include "Engine/Audio.h"

#include "Engine/Particle.h"

#include "Component/Gold.h"

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
        SetScale({ 1, 1 });
	}
	else if (IsInside(Map::outer_lower_right))
	{
        SetVelocity({ 0, speed * info.speed_scale });
        SetScale({ 1, 1 });
	}
	else if (IsInside(Map::outer_upper_right))
	{
        SetVelocity({ -speed * info.speed_scale, 0 });
        SetScale({ -1, 1 });
	}
	else if (IsInside(Map::outer_upper_left))
	{
        SetVelocity({ 0, -speed * info.speed_scale });
        SetScale({ -1, 1 });
	}

	if (tilt_count > 0.0)
    {
        tilt_count -= dt;
        tilt_amount -= tilt_decrease * dt;
		SetRotation(tilt_amount);
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
	Math::vec2 position = GetPosition();
	//image->Draw(static_cast<int>(position.x) - 528 / 8, static_cast<int>(position.y), 528 / 4, 350 / 4);
    //image->Draw(camera_matrix * Math::TranslationMatrix(Math::ivec2{ static_cast<int>(position.x) - 528 / 8, static_cast<int>(position.y) }));
    GAM200::GameObject::Draw(camera_matrix);
}

// Check to change direction
bool Monster::IsInside(Math::vec2 target_position) const
{
	Math::vec2 positioin = GetPosition();

	if (positioin.x >= target_position.x - offset / 2 &&
		positioin.x <= target_position.x + offset / 2 &&
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

	Math::vec2 particle_posistion = GetPosition();
    tilt_amount                   = (rand() % 20 - 10) / 80.0 * PI;
    tilt_count                    = tilt_time;
    tilt_decrease                 = tilt_amount / tilt_time;
	//Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::Hit>>()->Emit(1, particle_posistion, { 0, 0 }, { 0, 0 }, 3.14159265358979323846 / 2);
    Engine::GetGameStateManager().GetGSComponent<GAM200::ParticleManager<Particles::FontParticle>>()->Emit(1, particle_posistion, { 0, 0 }, { rand() % 30 - 15.0, 50.0 }, 3.14159265358979323846 / 2, damage);
}
