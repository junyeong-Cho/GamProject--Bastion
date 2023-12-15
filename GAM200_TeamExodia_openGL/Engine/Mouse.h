/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mouse.h
Project:    GAM200_TeamExodia_openGL
Author:     Junyeong Cho
Created:    October 6, 2023
Updated:    October 6, 2023
*/

#pragma once

#include <SDL2/SDL.h>

#include "../Engine/Vec2.h"

namespace GAM200
{
	class Mouse
	{
	public:
		enum class MouseButtons
		{
			LEFT,
			RIGHT,
			NONE,
		};

		enum class MouseState
		{
			PRESSED,
			RELEASED,
		};

		enum class MouseWheel
		{
			Up,
			Down,
			NONE,
		};

		Mouse();

		void		 Update();
		void		 SetMouseDown(MouseButtons button, bool value);
		//~Mouse() = default;

		void         HandleEvent(SDL_Event& event);


		bool         MouseDown(MouseButtons button);
		bool		 MouseJustPressed(MouseButtons button);
		bool		 MouseJustReleased(MouseButtons button);
		
		bool		 WheelIsMoved();

		Math::vec2   GetMousePosition();

		//MouseButtons MouseButton()
		//{
		//	if (mouse_event.button.button == SDL_BUTTON_LEFT)
		//	{
		//		return MouseButtons::LEFT;
		//	}
		//	else if (mouse_event.button.button == SDL_BUTTON_RIGHT)
		//	{
		//		return MouseButtons::RIGHT;
		//	}
		//	return MouseButtons::NONE;  
		//}

		GAM200::Mouse::MouseButtons convert_opengl_to_gam200(SDL_Event& mouse_event) {
			switch (mouse_event.button.button)
			{
			case SDL_BUTTON_LEFT:
				return GAM200::Mouse::MouseButtons::LEFT;
			case SDL_BUTTON_RIGHT:
				return GAM200::Mouse::MouseButtons::RIGHT;
			default:
				return GAM200::Mouse::MouseButtons::NONE;
			}
		}

		MouseWheel  MouseWheelDirection()
		{
			if (mouse_event.wheel.y > 0)
			{
				return MouseWheel::Up;
			}
			else if (mouse_event.wheel.y < 0)
			{
				return MouseWheel::Down;
			}
			return MouseWheel::NONE;
		}

	private:
		SDL_Event mouse_event;

		Math::vec2 mouse_position;

		bool is_pressed = false;
		bool wheel_moved = false;

		std::vector<bool> buttons_down;
		std::vector<bool> previous_buttons_down;

	};
}