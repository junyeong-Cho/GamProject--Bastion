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


//이름이 HandleEvent인 이유는 GameStateManager에서 HandleEvent를 호출하기 때문임
//간단하게 Update 기능을 수행한다고 생각하면 된다.
void GAM200::Mouse::HandleEvent(SDL_Event& event)
{
	mouse_event = event;
}


bool GAM200::Mouse::MouseIsPressed()
{
	if (mouse_event.type == SDL_MOUSEBUTTONDOWN)
	{
		return true;
	}

	return false;

}

Math::vec2 GAM200::Mouse::GetMousePosition()
{
	if (mouse_event.type == SDL_MOUSEMOTION)
	{
		mouse_position.x = mouse_event.motion.x;
		mouse_position.y = mouse_event.motion.y;
	}

	return mouse_position;
}



