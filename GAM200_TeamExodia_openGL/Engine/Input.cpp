/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.cpp
Project:    GAM200 Engine
Author:     Junyeong Cho
Created:    October 5, 2023
Updated:    October 5, 2023
*/


#include "Input.h"
#include "Engine.h"

#include <SDL2/SDL.h>
#include "ImGuiHelper.h"

GAM200::Input::Input()
{
    keys_down.resize(static_cast<int>(Keys::Unknown));
    previous_keys_down.resize(static_cast<int>(Keys::Unknown));
    buttons_down.resize(static_cast<int>(MouseButtons::NONE));
    previous_buttons_down.resize(static_cast<int>(MouseButtons::NONE));
}

void GAM200::Input::Update()
{

    //SDL_PollEvent�� ���ο��� ȣ���ϸ�, HandleEvent�� Ű���� �̺�Ʈ���� ó���ϰ���
    //������ instance�� ���� �޾ƿ��� ���̾����� �ʹ� ������...
    previous_keys_down = keys_down;
    previous_buttons_down = buttons_down;

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        ImGuiHelper::FeedEvent(event); 
        HandleEvent(event);
    }

}


GAM200::Input::Keys convertKey_opengl_to_gam200(SDL_Keycode sdl_key)
{
    switch (sdl_key)
    {
    case SDLK_a:
	    return GAM200::Input::Keys::A;
    case SDLK_b:
        return GAM200::Input::Keys::B;
    case SDLK_c:
        return GAM200::Input::Keys::C;
    case SDLK_d:
        return GAM200::Input::Keys::D;
    case SDLK_e:
        return GAM200::Input::Keys::E;
    case SDLK_f:    
        return GAM200::Input::Keys::F;
	case SDLK_g:
		return GAM200::Input::Keys::G;
    case SDLK_h:
	    return GAM200::Input::Keys::H;
    case SDLK_i:
		return GAM200::Input::Keys::I;
	case SDLK_j:
        return GAM200::Input::Keys::J;
    case SDLK_k:
        return GAM200::Input::Keys::K;
    case SDLK_l:
        return GAM200::Input::Keys::L;
	case SDLK_m:
		return GAM200::Input::Keys::M;
	case SDLK_n:
		return GAM200::Input::Keys::N;
	case SDLK_o:
		return GAM200::Input::Keys::O;
	case SDLK_p:
        return GAM200::Input::Keys::P;
	case SDLK_q:
		return GAM200::Input::Keys::Q;
	case SDLK_r:
		return GAM200::Input::Keys::R;
	case SDLK_s:
		return GAM200::Input::Keys::S;
	case SDLK_t:
		return GAM200::Input::Keys::T;
	case SDLK_u:
		return GAM200::Input::Keys::U;
	case SDLK_v:
		return GAM200::Input::Keys::V;
	case SDLK_w:
		return GAM200::Input::Keys::W;
	case SDLK_x:
        return GAM200::Input::Keys::X;
    case SDLK_y:
		return GAM200::Input::Keys::Y;
	case SDLK_z:
        return GAM200::Input::Keys::Z;
    case SDLK_SPACE:
		return GAM200::Input::Keys::Space;
    case SDLK_RETURN:
        return GAM200::Input::Keys::Enter;
    case SDLK_LEFT:
        return GAM200::Input::Keys::Left;
    case SDLK_UP:
        return GAM200::Input::Keys::Up;
	case SDLK_RIGHT:
        return GAM200::Input::Keys::Right;
    case SDLK_DOWN:
        return GAM200::Input::Keys::Down;
    case SDLK_ESCAPE:
		return GAM200::Input::Keys::Escape;
    case SDLK_BACKQUOTE:
        return GAM200::Input::Keys::Tidle;
    case SDLK_1:
        return GAM200::Input::Keys::_1;
    case SDLK_2:
        return GAM200::Input::Keys::_2;
    case SDLK_3:
        return GAM200::Input::Keys::_3;
    case SDLK_4:
        return GAM200::Input::Keys::_4;
    case SDLK_5:
        return GAM200::Input::Keys::_5;
    case SDLK_6:
        return GAM200::Input::Keys::_6;
    case SDLK_7:
        return GAM200::Input::Keys::_7;
    case SDLK_8:
        return GAM200::Input::Keys::_8;
    case SDLK_9:
        return GAM200::Input::Keys::_9;
    case SDLK_0:
        return GAM200::Input::Keys::_0;
    case SDLK_TAB:
        return GAM200::Input::Keys::Tab;
    case SDLK_LSHIFT:
        return GAM200::Input::Keys::L_Shift;
    }

    return GAM200::Input::Keys::Unknown;
}


void GAM200::Input::SetKeyDown(Keys key, bool value)
{
    keys_down[static_cast<int>(key)] = value;
}

void GAM200::Input::SetMouseDown(MouseButtons button, bool value)
{
    buttons_down[static_cast<int>(button)] = value;
}


void GAM200::Input::HandleEvent(SDL_Event& event)
{
    mouse_event = event;
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        Keys key = convertKey_opengl_to_gam200(event.key.keysym.sym);

        if (key != Keys::Unknown)
        {
            bool is_pressed = (event.type == SDL_KEYDOWN);

            if (is_pressed && event.key.repeat == 0)  
            {
                Engine::GetLogger().LogDebug("Key Pressed");
            }
            else if (!is_pressed)
            {
                Engine::GetLogger().LogDebug("Key Released");
            }

            SetKeyDown(key, is_pressed);
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        MouseButtons buttons = convertButton_opengl_to_gam200(event);

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

bool GAM200::Input::WheelIsMoved()
{
    if (wheel_moved)
    {
        // ������ ���� �ʱ�ȭ
        wheel_moved = false;

        return true;
    }

    return false;
}

Math::vec2 GAM200::Input::GetMousePosition()
{
    return mouse_position;
}

bool GAM200::Input::keyDown(Keys key)
{
    return keys_down[static_cast<int>(key)];
}

bool GAM200::Input::MouseDown(MouseButtons button)
{
    return buttons_down[static_cast<int>(button)];
}

bool GAM200::Input::KeyJustPressed(Keys key)
{
    return keys_down[static_cast<int>(key)] == true && previous_keys_down[static_cast<int>(key)] == false;
}

bool GAM200::Input::KeyJustReleased(Keys key)
{
    return keys_down[static_cast<int>(key)] == false && previous_keys_down[static_cast<int>(key)] == true;
}

bool GAM200::Input::MouseJustPressed(MouseButtons button)
{
    return buttons_down[static_cast<int>(button)] == true && previous_buttons_down[static_cast<int>(button)] == false;
}

bool GAM200::Input::MouseJustReleased(MouseButtons button)
{
    return buttons_down[static_cast<int>(button)] == false && previous_buttons_down[static_cast<int>(button)] == true;
}