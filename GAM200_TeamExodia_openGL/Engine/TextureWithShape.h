/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    GAM200_TeamExodia
Author:     Junyeong Cho
Created:    October 3, 2023
Updated:    October 10, 2023
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
	class TextureWithShape
	{
	public:

		enum class TextureType
		{
			RECTANGLE,
			TRIANGLE,
			CIRCLE,
		} texturetype;


		friend class TextureManager;
		friend class Font;

		TextureWithShape(const std::filesystem::path& file_path, TextureType texturetype);

		~TextureWithShape();


		void Draw(int x, int y, int width, int height);

		void Draw(int x, int y, float radius, int points);

	private:
		int imageWidth  = 0;
		int imageHeight = 0;

		int windowWidth = Engine::GetWindow().GetSize().x;
		int windowHeight = Engine::GetWindow().GetSize().y;


		unsigned char* image;


		unsigned char* LoadImageFromFile(const std::filesystem::path& filePath);

		void DrawRect(int x1, int y1, int x2, int y2);
		void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
		void DrawCircle(int x, int y, float radius, int points);


		GLuint textureID;


	};
}

