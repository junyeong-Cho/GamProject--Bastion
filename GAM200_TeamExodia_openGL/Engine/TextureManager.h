/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.h
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 3, 2023
*/

#pragma once

#include <filesystem>
#include <map>

namespace GAM200
{
	class Texture;

	class TextureManager
	{
	public:
		Texture* Load(const std::filesystem::path& file_path);

		void Unload();

	private:

		std::map< std::filesystem::path, Texture*> textures;

	};
}