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


//�̸��� HandleEvent�� ������ GameStateManager���� HandleEvent�� ȣ���ϱ� ������
//�����ϰ� Update ����� �����Ѵٰ� �����ϸ� �ȴ�.
void GAM200::Mouse::HandleEvent(SDL_Event& event)
{
	mouse_event = event;


	//������ WheelIsMoved�ȿ� �־����� �̷��� �ٲ� ������
	//WheelIsMoved�� ȣ��Ǵ� ������ HandleEvent���� �ʱ� ������
	//�ӵ� �� �����ٷ��� ����ٰ� ����
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
		// ������ ���� �ʱ�ȭ
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



