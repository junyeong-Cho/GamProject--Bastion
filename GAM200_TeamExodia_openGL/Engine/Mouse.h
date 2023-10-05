/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mouse.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 6, 2023
Updated:    October 6, 2023
*/

#pragma once

#include <GL/glew.h>
#include <GL/GLU.h>
#include <GL/GL.h>

#include <SDL2/SDL.h>

namespace GAM200
{
	class Mouse
	{
	public:
		enum class MouseButtons
		{
			LEFT,
			RIGHT,
		};

		Mouse()  = default;
		~Mouse() = default;

		void         Update();

		bool         MouseIsPressed();
		
		MouseButtons MouseButton()
		{
			if (mouse_event.button.button == SDL_BUTTON_LEFT)
			{
				return MouseButtons::LEFT;
			}
			else if (mouse_event.button.button == SDL_BUTTON_RIGHT)
			{
				return MouseButtons::RIGHT;
			}
		}

		

	private:
		SDL_Event mouse_event;


	};
}