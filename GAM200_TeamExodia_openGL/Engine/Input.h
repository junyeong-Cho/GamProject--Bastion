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
			_1, _2, _3, _4, _5, _6, _7, _8, _9, _0, Tab,
			Unknown
		};

		Input();

		void Update();
		void SetKeyDown(Keys key, bool value);

		void HandleEvent(SDL_Event& event);

		bool keyDown(Keys key);
		bool KeyJustPressed(Keys key);
		bool KeyJustReleased(Keys key);

	private:
		std::vector<bool> keys_down;
		std::vector<bool> previous_keys_down;
	};
}