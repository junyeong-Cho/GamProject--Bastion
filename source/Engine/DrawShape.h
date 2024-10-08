/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  DrawShape.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October 4, 2023
Updated:    October 4, 2023
*/

#pragma once


#include <GL/glew.h>

#include "Engine/Normalization.h" 
#include "Engine/GameState.h"
#include "Engine/Vec2.h"
#include "Engine/Rect.h"
#include "Engine/Matrix.h"


#if !defined(__EMSCRIPTEN__)
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

		void DrawRectangle_NoFill(int x, int y, int width, int height);
		void DrawRectangle_NoFill_WithPoints(int x1, int y1, int x2, int y2);
		void DrawRectangle_NoFill_WithPoints(Math::vec2 topLeft, Math::vec2 topRight, Math::vec2 bottomLeft, Math::vec2 bottomRight);

		void DrawRectangle_NoFill_WithBoundaries(Math::rect world_boundary, Math::TransformationMatrix);

		void DrawCircle(int x, int y, int radius, int area);



		void SetColor(float r, float g, float b, float a);

		void SetLineWidth(float width);


	private:


		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float lineWidth = 1.0f;

		int x = 0;
		int y = 0;

		int width = 0;
		int height = 0;

		int radius = 0;



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

#else

#endif