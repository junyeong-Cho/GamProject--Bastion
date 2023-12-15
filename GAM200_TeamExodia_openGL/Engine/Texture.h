/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 10, 2023
*/


#pragma once


#include <iostream>
#include <filesystem>


#include "OriginPosition.h"

#include "DrawShape.h"


#include "Matrix.h"
#include "Vec2.h"


namespace GAM200
{
	class Texture
	{
	public:

		
		friend class TextureManager;
		friend class Font;

		enum class TextureType
		{
			RECTANGLE,
			TRIANGLE,
			CIRCLE,
		} texturetype;


		Texture() { };

		~Texture();


		Texture(const std::filesystem::path& file_path, TextureType texturetype);
		Texture(const std::filesystem::path& file_path);


		//void DrawRect(Math::vec2 screenTopLeft, Math::vec2 screenBottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size);

		void Draw(int x, int y, int width, int height);

		void Draw(int x, int y, float radius, int points);

		void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);

		void DrawRect(Math::vec2 topLeft, Math::vec2 topRight, Math::vec2 bottomLeft, Math::vec2 bottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size);

		void Draw(Math::TransformationMatrix display_matrix);
		

		//void DrawRect(Math::vec2 screenTopLeft, Math::vec2 screenTopRight, Math::vec2 screenBottomLeft, Math::vec2 screenBottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size);
		//void DrawRect(Math::vec2 topLeft, Math::vec2 topRight, Math::vec2 bottomLeft, Math::vec2 bottomRight, Math::ivec2 texel_position, Math::ivec2 frame_size);

		Math::ivec2 GetSize();

		GLuint getTextureID() const { return textureID; }



	private:


		Texture(const std::filesystem::path& file_path, Math::ivec2 text_size);



		unsigned int GetPixel(Math::ivec2 texel);

		
		Math::ivec2 imageSize;


		int imageWidth  = 0;
		int imageHeight = 0;

		


		unsigned char* image;

		unsigned int* image_data = nullptr;

		unsigned char* LoadImageFromFile(const std::filesystem::path& filePath);

		void DrawRect(int x1, int y1, int x2, int y2);
		void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
		void DrawCircle(int x, int y, float radius, int points);

		

		GLuint textureID;


	};
}

