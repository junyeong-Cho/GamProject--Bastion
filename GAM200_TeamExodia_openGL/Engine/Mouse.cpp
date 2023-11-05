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


//이름이 HandleEvent인 이유는 GameStateManager에서 HandleEvent를 호출하기 때문임
//간단하게 Update 기능을 수행한다고 생각하면 된다.
void GAM200::Mouse::HandleEvent(SDL_Event& event)
{
	mouse_event = event;


	//원래는 WheelIsMoved안에 있었으나 이렇게 바꾼 이유는
	//WheelIsMoved가 호출되는 시점이 HandleEvent보다 늦기 때문에
	//속도 좀 높여줄려고 여기다가 넣음
	if (event.type == SDL_MOUSEWHEEL)
	{
		wheel_moved = true;
	}
}


bool GAM200::Mouse::MouseIsPressed()
{
	if (mouse_event.type == SDL_MOUSEBUTTONDOWN)
	{
		return true;
	}

	return false;

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

    return mouse_position;
}



