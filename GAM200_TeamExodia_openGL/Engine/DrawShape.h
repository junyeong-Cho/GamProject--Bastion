/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  DrawShape.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 4, 2023
Updated:    October 4, 2023
*/

#pragma once


#include <GL/glew.h>
#include <GL/GL.h>


#include "../Engine/Vec2.h"
//#include "../Engine/Normalize.h"
#include "../Engine/GameState.h"
#include "../Engine/Engine.h"




namespace GAM200
{
	class DrawShape
	{
	public:
		DrawShape() = default;
		~DrawShape() = default;

		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(Math::ivec2 start, Math::ivec2 end);



		void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
		void DrawTriangle(int x, int y, int width, int height);


		
		
		void DrawRectangle(int x, int y, int width, int height);

		void DrawRectangleWithPoints(int x1, int y1, int x2, int y2);



		void DrawCircle(int x, int y, int radius, int area);
		


		void SetColor(float r, float g, float b, float a);

		void SetLineWidth(float width);


	private:
		int windowWidth = Engine::GetWindow().GetSize().x;
		int windowHeight = Engine::GetWindow().GetSize().y;

		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float lineWidth = 1.0f;

		int x = 0;
		int y = 0;

		int width = 0;
		int height = 0;

		int radius = 0;

		//float width = 0;


		float NormalizeX(int x, int windowWidth)
		{
			float nx = (static_cast<float>(x) / (windowWidth / 2)) - 1.0f;

			switch (Engine::GetWindow().GetOriginPosition())
			{
			case OriginPosition::RIGHT_DOWN:
			case OriginPosition::RIGHT_UP:
				nx = -nx; // Flip the X-axis for right-oriented origins
				break;
			default:
				break;
			}

			return nx;
		}

		float NormalizeY(int y, int windowHeight)
		{
			float ny = (static_cast<float>(y) / (windowHeight / 2)) - 1.0f;

			switch (Engine::GetWindow().GetOriginPosition())
			{
			case OriginPosition::LEFT_UP:
			case OriginPosition::RIGHT_UP:
				ny = -ny; // Flip the Y-axis for bottom-oriented origins
				break;
			default:
				break;
			}

			return ny;
		}



		enum class Whichshape
		{
			None,
			Line,
			Triangle,
			Rectangle,
			Circle,
		};

	};
}