/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Junyeong Cho
Created:    March 14, 2023
Updated:    September 26, 2023
*/

#include "TextureManager.h"
#include "Texture.h"

#include "Engine.h"


//std::map< std::filesystem::path, Texture*> textures;
CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& file_path)
{
	auto it = textures.find(file_path);

	if (it != textures.end())
	{
		return it->second;
	}
	else
	{
		Texture* texture = new Texture(file_path);
		textures[file_path] = texture;

		Engine::GetLogger().LogEvent("Loaded texture: " + file_path.generic_string());

		return texture;
	}


}


void CS230::TextureManager::Unload()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		delete it->second;
	}

	textures.clear();
}
