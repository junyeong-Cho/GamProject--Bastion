/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Particle.cpp
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    November 1, 2023
Updated:    November 1, 2023
*/

#include "Particle.h"

GAM200::Particle::Particle(const std::filesystem::path& sprite_file) : GameObject({ 0, 0 })
{
	life = 0.0;
    num  = 0.0;
	AddGOComponent(new GAM200::Sprite(sprite_file, (this)));
}

void GAM200::Particle::Start(Math::vec2 position, Math::vec2 velocity, double max_life)
{

	SetPosition({ position.x, position.y });
	SetVelocity({ (double)velocity.x , (double)velocity.y });

	life = max_life;

	GAM200::Sprite* sprite = GetGOComponent<GAM200::Sprite>();

	if (sprite != nullptr)
	{
		sprite->PlayAnimation(0);
	}

}

void GAM200::Particle::Start(Math::vec2 position, Math::vec2 velocity, double max_life, double dmg)
{
    SetPosition({ position.x, position.y });
    SetVelocity({ (double)velocity.x, (double)velocity.y });

    life = max_life;
    num  = dmg;

    GAM200::Sprite* sprite = GetGOComponent<GAM200::Sprite>();

    if (sprite != nullptr)
    {
        sprite->PlayAnimation(0);
    }
}

void GAM200::Particle::Update(double dt)
{
	if (Alive() == true)
	{
		life -= dt;

		GameObject::Update(dt);
	}
}


void GAM200::Particle::Draw(Math::TransformationMatrix camera_matrix)
{
	if (Alive())
	{
		GameObject::Draw(camera_matrix);
	}
}


