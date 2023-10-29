/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 30, 2023
Updated:    October 30, 2023
*/


#pragma once


#include <GL/glew.h>
#include <iostream>
#include <filesystem>


#include "OriginPosition.h"
#include "Normalization.h" 
#include "DrawShape.h"


#include "Engine.h"


#include "Matrix.h"
#include "Vec2.h"



namespace GAM200
{
	class Texture
	{
	public:

		friend class TextureManager;
		friend class Font;

		Texture(const std::filesystem::path& file_path);

		Texture(GLuint texID);


		void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);

		void Draw(Math::TransformationMatrix display_matrix);


		Math::ivec2 GetSize();


	private:

		unsigned int GetPixel(Math::ivec2 texel);

		Math::ivec2 imageSize;

		int imageWidth = 0;
		int imageHeight = 0;

		int windowWidth = Engine::GetWindow().GetSize().x;
		int windowHeight = Engine::GetWindow().GetSize().y;


		unsigned char* image;



		GLuint textureID;




	};
}

