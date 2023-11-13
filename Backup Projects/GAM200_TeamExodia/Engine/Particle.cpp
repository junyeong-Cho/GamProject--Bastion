#include "Particle.h"

CS230::Particle::Particle(const std::filesystem::path& sprite_file) : GameObject({ 0, 0 })
{
	life = 0.0;
	AddGOComponent(new CS230::Sprite(sprite_file, (this)));
}

void CS230::Particle::Start(Math::vec2 position, Math::vec2 velocity, double max_life)
{

	SetPosition({ position.x, position.y });
	SetVelocity({ (double)velocity.x , (double)velocity.y });

	life = max_life;

	CS230::Sprite* sprite = GetGOComponent<CS230::Sprite>();

	if (sprite != nullptr)
	{
		sprite->PlayAnimation(0);
	}

}

void CS230::Particle::Update(double dt)
{
	if (Alive() == true)
	{
		life -= dt;

		GameObject::Update(dt);
	}
}


void CS230::Particle::Draw(Math::TransformationMatrix camera_matrix)
{
	if (Alive())
	{
		GameObject::Draw(camera_matrix);
	}
}


