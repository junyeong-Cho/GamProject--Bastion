/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 8,  2023
Updated:    September 26, 2023
*/


#include "Background.h"
#include"../Engine/Sprite.h"



void Background::Add(const std::filesystem::path& texturePath, double speed)
{
	//backgrounds.push_back(ParallaxLayer({texturePath, speed}));

	CS230::Texture* texture = Engine::GetTextureManager().Load(texturePath);
	backgrounds.push_back(ParallaxLayer({ texture, speed }));
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera) 
{
	for (ParallaxLayer& background : backgrounds) 
	{
		background.texture->Draw(Math::TranslationMatrix(Math::vec2{ 0 - camera.GetPosition().x * background.speed, 0 - camera.GetPosition().y }));
	}
}


Math::ivec2 Background::GetSize()
{
	return backgrounds.back().texture->GetSize();
}
