/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mouse.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 6, 2023
Updated:    October 6, 2023
*/


#include "Mouse.h"
#include "Engine.h"
#include "Normalization.h"

#include <SDL2/SDL.h>
#include "ImGuiHelper.h"

GAM200::Mouse::Mouse() {
	buttons_down.resize(static_cast<int>(MouseButtons::NONE));
	previous_buttons_down.resize(static_cast<int>(MouseButtons::NONE));
}

void GAM200::Mouse::Update() {
	previous_buttons_down = buttons_down;

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		ImGuiHelper::FeedEvent(event);
		HandleEvent(event);
	}
}

//이름이 HandleEvent인 이유는 GameStateManager에서 HandleEvent를 호출하기 때문임
//간단하게 Update 기능을 수행한다고 생각하면 된다.
void GAM200::Mouse::HandleEvent(SDL_Event& event)
{
	//mouse_event = event;

	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		MouseButtons buttons = convert_opengl_to_gam200(event);

		if (buttons != MouseButtons::NONE) {
			if (mouse_event.type == SDL_MOUSEBUTTONDOWN) {
				is_pressed = true;
			}
			else if (mouse_event.type == SDL_MOUSEBUTTONUP) {
				is_pressed = false;
			}

			SetMouseDown(buttons, is_pressed);
		}
	}
	//원래는 WheelIsMoved안에 있었으나 이렇게 바꾼 이유는
	//WheelIsMoved가 호출되는 시점이 HandleEvent보다 늦기 때문에
	//속도 좀 높여줄려고 여기다가 넣음
	if (event.type == SDL_MOUSEWHEEL)
	{
		wheel_moved = true;
	}

	int windowWidth = Engine::GetWindow().GetSize().x;
	int windowHeight = Engine::GetWindow().GetSize().y;

	if (mouse_event.type == SDL_MOUSEMOTION)
	{
		mouse_position.x = mouse_event.motion.x;
		mouse_position.y = mouse_event.motion.y;


		OriginPosition origin = Engine::GetWindow().GetOriginPosition();
		if (origin == OriginPosition::RIGHT_UP || origin == OriginPosition::RIGHT_DOWN)
		{
			mouse_position.x = Engine::GetWindow().GetSize().x - mouse_position.x;
		}
		if (origin == OriginPosition::LEFT_DOWN || origin == OriginPosition::RIGHT_DOWN)
		{
			mouse_position.y = Engine::GetWindow().GetSize().y - mouse_position.y;
		}
	}

	// Log mouse event (pressed or released)
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		Engine::GetLogger().LogDebug((event.type == SDL_MOUSEBUTTONDOWN) ? "Mouse Pressed" : "Mouse Released");
	}
}

bool GAM200::Mouse::WheelIsMoved()
{
	if (wheel_moved)
	{
		// 움직임 상태 초기화
		wheel_moved = false;

		return true;
	}

	return false;
}

Math::vec2 GAM200::Mouse::GetMousePosition()
{
	return mouse_position;
}


void GAM200::Mouse::SetMouseDown(MouseButtons button, bool value)
{
	buttons_down[static_cast<int>(button)] = value;
}

bool GAM200::Mouse::MouseDown(MouseButtons button)
{
	return buttons_down[static_cast<int>(button)];
}

bool GAM200::Mouse::MouseJustPressed(MouseButtons button)
{
	return buttons_down[static_cast<int>(button)] == true && previous_buttons_down[static_cast<int>(button)] == false;
}

bool GAM200::Mouse::MouseJustReleased(MouseButtons button)
{
	return buttons_down[static_cast<int>(button)] == false && previous_buttons_down[static_cast<int>(button)] == true;
}



