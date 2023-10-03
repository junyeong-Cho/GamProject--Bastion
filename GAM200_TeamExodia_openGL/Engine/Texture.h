/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 3, 2023
*/

/*
#pragma once

#include <doodle/image.hpp>

#include "Vec2.h"

#include "Matrix.h"


namespace CS230
{
	class Texture
	{
	public:

		friend class TextureManager;
		friend class Font;

		void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);
		void Draw(Math::TransformationMatrix display_matrix);

		Math::ivec2 GetSize();

		Texture() {};


	private:

		Texture(doodle::Image&& doodle_image);

		unsigned int GetPixel(Math::ivec2 texel);

		Texture(const std::filesystem::path& file_path);


		doodle::Image image;
	};
}
*/
