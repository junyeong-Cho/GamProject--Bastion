/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.h
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 5, 2023
Updated:    October 5, 2023
*/

#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "../Engine/Vec2.h"

namespace GAM200
{
	class Input
	{
	public:
		enum class Keys
		{
			A, B, C, D, E, F, G, H, I, J, K, L, M, N,
			O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Space, Enter, Left, Up, Right, Down, Escape, Tidle,
			_1, _2, _3, _4, _5, _6, _7, _8, _9, _0, Tab,L_Shift,
			Unknown
		};

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

		Input();

		void Update();

		void SetKeyDown(Keys key, bool value);
		void SetMouseDown(MouseButtons button, bool value);

		void HandleEvent(SDL_Event& event);

		bool keyDown(Keys key);
		bool KeyJustPressed(Keys key);
		bool KeyJustReleased(Keys key);

		bool MouseDown(MouseButtons button);
		bool MouseJustPressed(MouseButtons button);
		bool MouseJustReleased(MouseButtons button);

		bool WheelIsMoved();

		Math::vec2   GetMousePosition();

		GAM200::Input::MouseButtons convertButton_opengl_to_gam200(SDL_Event& event) {
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				return GAM200::Input::MouseButtons::LEFT;
			case SDL_BUTTON_RIGHT:
				return GAM200::Input::MouseButtons::RIGHT;
			default:
				return GAM200::Input::MouseButtons::NONE;
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
		std::vector<bool> keys_down;
		std::vector<bool> previous_keys_down;

		SDL_Event mouse_event;

		Math::vec2 mouse_position;

		bool is_pressed = false;
		bool wheel_moved = false;

		std::vector<bool> buttons_down;
		std::vector<bool> previous_buttons_down;
	};
}